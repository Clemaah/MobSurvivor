// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "Http.h"
#include "Json.h"
#include "HttpManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGetScoresSignature, const TArray<UScore*>&, Scores);

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

	void Initialize(UMobSurvivorGameInstance* InGameInstance);

	UFUNCTION(BlueprintCallable)
	void SendRequest(const FString& Action, const TMap<FString, FString>& Arguments);

	void ProcessResponse(const FString Action, TArray<TSharedPtr<FJsonValue>>& ResponseArray);

	void Connection(TSharedPtr<FJsonObject> ResponseObject);

	void GetUser(TSharedPtr<FJsonObject> ResponseObject);

	void GetLeaderBoard(TArray<TSharedPtr<FJsonValue>>& ResponseArray);

	void InsertUser(TSharedPtr<FJsonObject> ResponseObject);

	void InsertScore(TSharedPtr<FJsonObject> ResponseObject);

};
