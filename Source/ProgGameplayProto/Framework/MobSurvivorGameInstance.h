// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MobSurvivorGameInstance.generated.h"

class UStartParameters;
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

	UPROPERTY(BlueprintReadWrite, Category = "SaveSettings")
	FString SaveGameSlotName;

	UPROPERTY(BlueprintReadWrite, Category = "SaveSettings")
	UMobSurvivorSaveGame* SaveGameInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StartParameters", Meta = (ShowOnlyInnerProperties))
	UStartParameters* StartDataReference;

	void OnStart() override;

	UFUNCTION(BlueprintCallable, Category = "GameManager")
	void LoadGame();

	UFUNCTION(BlueprintCallable, Category = "GameManager")
	void SaveGame();

private:
	void LogResultOfSaveGame(const bool IsSaved);
};
