// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MobSurvivorGameInstance.generated.h"

class UMobSurvivorSaveGame;
/**
 * 
 */
UCLASS()
class PROGGAMEPLAYPROTO_API UMobSurvivorGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMobSurvivorGameInstance();

	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	FString SaveGameSlotName;

	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	UMobSurvivorSaveGame* SaveGameInstance;

	UFUNCTION(BlueprintCallable, Category = "GameManager")
	void LoadGame();

	UFUNCTION(BlueprintCallable, Category = "GameManager")
	void SaveGame();

private:
	void LogResultOfSaveGame(const bool IsSaved);
};
