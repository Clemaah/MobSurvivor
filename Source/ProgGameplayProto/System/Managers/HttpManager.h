// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "ProgGameplayProto/System/MenuGameMode.h"
#include "ProgGameplayProto/System/MobSurvivorGameInstance.h"
#include "HttpManager.generated.h"


/**
 *
 */
UCLASS()
class PROGGAMEPLAYPROTO_API UHttpManager : public UObject
{
	GENERATED_BODY()

	FString BaseUrl = "http://mob-survivor.alwaysdata.net/";

public:
	AMenuGameMode* GameMode;

	UMobSurvivorGameInstance* GameInstance;

	void Initialize(UMobSurvivorGameInstance* InGameInstance, AMenuGameMode* InGameMode);

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
