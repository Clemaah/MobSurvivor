#include "HttpManager.h"

#include "ProgGameplayProto/Score.h"
#include "ProgGameplayProto/System/MobSurvivorGameInstance.h"

void UHttpManager::Initialize(UMobSurvivorGameInstance* InGameInstance)
{
    GameInstance = InGameInstance;
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

                TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(Response->GetContentAsString());
                TArray<TSharedPtr<FJsonValue>> ResponseArray;

                if (FJsonSerializer::Deserialize(JsonReader, ResponseArray))
                {
                    ProcessResponse(Request->GetURL().Mid(BaseUrl.Len()), ResponseArray);
                }

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

void UHttpManager::ProcessResponse(const FString Action, TArray<TSharedPtr<FJsonValue>>& ResponseArray)
{
    if (Action == "connect")
    {
        Connection(ResponseArray[0]->AsObject());
        return;
    }

    if (Action == "getUser")
    {
        GetUser(ResponseArray[0]->AsObject());
        return;
    }

    if (Action == "getLeaderBoard")
    {
        GetLeaderBoard(ResponseArray);
        return;
    }

    if (Action == "insertScore")
    {
        InsertScore(ResponseArray[0]->AsObject());
        return;
    }

    if (Action == "insertUser")
    {
        InsertUser(ResponseArray[0]->AsObject());
        return;
    }

    UE_LOG(LogTemp, Error, TEXT("Unknown action : %s"), *Action);
}








void UHttpManager::Connection(TSharedPtr<FJsonObject> ResponseObject)
{
}

void UHttpManager::GetUser(TSharedPtr<FJsonObject> ResponseObject)
{
}

void UHttpManager::GetLeaderBoard(TArray<TSharedPtr<FJsonValue>>& ResponseArray)
{
    TArray<UScore*> Scores;
    for (int i = 0; i < ResponseArray.Num(); ++i)
    {
        const TSharedPtr<FJsonObject> JSonObject = ResponseArray[i]->AsObject();
        Scores.Add(NewObject<UScore>());
        Scores[i]->Initialization(
            JSonObject->GetStringField("pseudo"),
            JSonObject->GetStringField("characterUsed"),
            JSonObject->GetStringField("weaponUsed"),
            JSonObject->GetStringField("projectileUsed"),
            JSonObject->GetNumberField("score")
        );
        UE_LOG(LogTemp, Display, TEXT("Score : %f"), Scores[i]->Score);
    }

    OnGetScoresDelegate.Broadcast(Scores);
}

void UHttpManager::InsertUser(TSharedPtr<FJsonObject> ResponseObject)
{
}

void UHttpManager::InsertScore(TSharedPtr<FJsonObject> ResponseObject)
{
}

