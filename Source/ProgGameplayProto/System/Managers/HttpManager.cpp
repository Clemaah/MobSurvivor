#include "HttpManager.h"

#include "Http.h"
#include "Score.h"
#include "ProgGameplayProto/System/GameUtils.h"
#include "ProgGameplayProto/System/MobSurvivorGameInstance.h"


void UHttpManager::Initialize(UMobSurvivorGameInstance* InGameInstance, AMenuGameMode* InGameMode)
{
    GameInstance = InGameInstance;
    GameMode = InGameMode;
}

void UHttpManager::GetToken(FString pseudo, FString password)
{
    TMap<FString, FString> arguments;
    arguments.Add("pseudo", pseudo);
    arguments.Add("password", password);

    SendRequest("getToken", arguments);
}

void UHttpManager::GetUser(FString token)
{
    TMap<FString, FString> arguments;
    arguments.Add("token", token);

    SendRequest("getUser", arguments);
}

void UHttpManager::GetLeaderBoard()
{
    TMap<FString, FString> arguments;
    SendRequest("getLeaderBoard", arguments);
}

void UHttpManager::InsertUser(FString email, FString pseudo, FString password)
{
    TMap<FString, FString> arguments;
    arguments.Add("email", email);
    arguments.Add("pseudo", pseudo);
    arguments.Add("password", password);

    SendRequest("insertUser", arguments);
}

void UHttpManager::InsertScore(FString token, FString character, FString weapon, FString projectile, int score)
{
    TMap<FString, FString> arguments;
    arguments.Add("token", token);
    arguments.Add("character", character);
    arguments.Add("weapon", weapon);
    arguments.Add("projectile", projectile);
    arguments.Add("score", FString::FromInt(score));

    SendRequest("insertScore", arguments);
}



void UHttpManager::SendRequest(const FString& Action, const TMap<FString, FString>& Arguments)
{
    FString url = BaseUrl + Action;
    FHttpModule& httpModule = FHttpModule::Get();

    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = httpModule.CreateRequest();
    TSharedRef<FJsonObject> RequestObject = MakeShared<FJsonObject>();

    for (auto Argument : Arguments)
        RequestObject->SetStringField(Argument.Key, Argument.Value);

    FString RequestContent;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestContent);
    FJsonSerializer::Serialize(RequestObject, Writer);

    Request->SetURL(url);
    Request->SetVerb("POST");
    Request->SetHeader("Content-Type", "application/json");
    Request->SetContentAsString(RequestContent);

    Request->OnProcessRequestComplete().BindLambda(
        [&](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccessfulConnection) mutable {
            if (bSuccessfulConnection) {
                UE_LOG(LogTemp, Log, TEXT("Server response: %s"), *(Response->GetContentAsString()));

                check(IsInGameThread());

                FString actionResponse = Request->GetURL().Mid(BaseUrl.Len());

                TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(Response->GetContentAsString());

                TArray<TSharedPtr<FJsonValue>> ResponseArray;
                TSharedPtr<FJsonObject> ResponseObject;


	            if (actionResponse == "getLeaderBoard" && FJsonSerializer::Deserialize(JsonReader, ResponseArray))
                    GetLeaderBoardResponse(ResponseArray);

                else if (FJsonSerializer::Deserialize(JsonReader, ResponseObject))
                    ProcessResponseObject(actionResponse, ResponseObject);

                else
                    UE_LOG(LogTemp, Error, TEXT("Failed to deserialize Server response"));
            }
            else {
                switch (Request->GetStatus()) {
                case EHttpRequestStatus::Failed_ConnectionError:
                    UE_LOG(LogTemp, Error, TEXT("Connection failed."));
                default:
                    UE_LOG(LogTemp, Error, TEXT("Request failed."));
                }
            }
        });
    Request->ProcessRequest();

    UE_LOG(LogTemp, Log, TEXT("Server request: %s; content:%s"), *url, *RequestContent);
}

void UHttpManager::ProcessResponseObject(const FString Action, TSharedPtr<FJsonObject>& ResponseObject)
{
    if (Action == "getToken")
    {
        GetTokenResponse(ResponseObject);
        return;
    }

    if (Action == "getUser")
    {
        GetUserResponse(ResponseObject);
        return;
    }

    if (Action == "insertScore")
    {
        InsertScoreResponse(ResponseObject);
        return;
    }

    if (Action == "insertUser")
    {
        InsertUserResponse(ResponseObject);
    }
}

void UHttpManager::GetTokenResponse(TSharedPtr<FJsonObject> ResponseObject)
{
    if (!ResponseObject->GetBoolField("success"))
    {
        GameMode->DisplayError(ResponseObject->GetStringField("message"));
        return;
    }

    FString token = ResponseObject->GetStringField("token");
    GameInstance->UpdatePlayerToken(token);
    GetUser(token);
}

void UHttpManager::GetUserResponse(TSharedPtr<FJsonObject> ResponseObject)
{
    if(!ResponseObject->GetBoolField("success"))
    {
        GameInstance->UpdatePlayerToken("");
        GameMode->DisplayError(ResponseObject->GetStringField("message"));
        return;
    }

    GameMode->Connect(ResponseObject->GetStringField("pseudo"));
    GameMode->DisplayMessage(ResponseObject->GetStringField("message"));
}

void UHttpManager::GetLeaderBoardResponse(TArray<TSharedPtr<FJsonValue>>& ResponseArray)
{
    TArray<FScore> ResScores;

    for (int i = 0; i < ResponseArray.Num(); ++i)
    {
        const TSharedPtr<FJsonObject> JSonObject = ResponseArray[i]->AsObject();
        FScore inScore;

        inScore.Pseudo = JSonObject->GetStringField("pseudo");
        inScore.Character = JSonObject->GetStringField("characterUsed");
        inScore.Weapon = JSonObject->GetStringField("weaponUsed");
        inScore.Projectile = JSonObject->GetStringField("projectileUsed");
        inScore.Score = JSonObject->GetNumberField("score");

        ResScores.Add(inScore);
    }

    GameMode->GetScores(ResScores);
}

void UHttpManager::InsertUserResponse(TSharedPtr<FJsonObject> ResponseObject)
{
    if (!ResponseObject->GetBoolField("success"))
    {
        GameMode->DisplayError(ResponseObject->GetStringField("message"));
        return;
    }

    GameMode->DisplayMessage(ResponseObject->GetStringField("message"));
}

void UHttpManager::InsertScoreResponse(TSharedPtr<FJsonObject> ResponseObject)
{
    if (!ResponseObject->GetBoolField("success"))
    {
        GameMode->DisplayError(ResponseObject->GetStringField("message"));
        return;
    }

    GameMode->DisplayMessage(ResponseObject->GetStringField("message"));
}

