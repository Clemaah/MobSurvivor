// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "UObject/ObjectMacros.h"

#include "MobSurvivorSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PROGGAMEPLAYPROTO_API UMobSurvivorSaveGame : public USaveGame
{
	GENERATED_BODY()

	UMobSurvivorSaveGame();

public:
	UPROPERTY(BlueprintReadWrite, Category = "Player Info")
	FString PlayerName;

	UPROPERTY(BlueprintReadWrite, Category = "Player Info")
	int32 PlayerAge;
};