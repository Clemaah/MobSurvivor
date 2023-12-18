// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "HttpManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGetScoresSignature, const TArray<UScore*>&, Scores);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStringResponseSignature, const FString&, String);

class UMobSurvivorGameInstance;
/**
 *
 */
UCLASS()
class PROGGAMEPLAYPROTO_API UHttpManager : public UObject
{
	GENERATED_BODY()

	UMobSurvivorGameInstance* GameInstance;

	FString BaseUrl = "http://localhost:3000/";


public:
	FOnGetScoresSignature OnGetScoresDelegate;

	FOnStringResponseSignature OnGetUserDelegate;

	FOnStringResponseSignature OnErrorDelegate;

	FOnStringResponseSignature OnMessageDelegate;

	void Initialize(UMobSurvivorGameInstance* InGameInstance);

	UFUNCTION(BlueprintCallable)
	void GetToken(FString pseudo, FString password);

	UFUNCTION(BlueprintCallable)
	void GetUser(FString token);

	UFUNCTION(BlueprintCallable)
	void GetLeaderBoard();

	UFUNCTION(BlueprintCallable)
	void InsertUser(FString email, FString pseudo, FString password);

	UFUNCTION(BlueprintCallable)
	void InsertScore(FString token, FString character, FString weapon, FString projectile, int score);

private:
	void SendRequest(const FString& Action, const TMap<FString, FString>& Arguments);

	void ProcessResponseObject(const FString Action, TSharedPtr<FJsonObject>& ResponseArray);

	void GetTokenResponse(TSharedPtr<FJsonObject> ResponseObject);

	void GetUserResponse(TSharedPtr<FJsonObject> ResponseObject);

	void GetLeaderBoardResponse(TArray<TSharedPtr<FJsonValue>>& ResponseArray);

	void InsertUserResponse(TSharedPtr<FJsonObject> ResponseObject);

	void InsertScoreResponse(TSharedPtr<FJsonObject> ResponseObject);

};
