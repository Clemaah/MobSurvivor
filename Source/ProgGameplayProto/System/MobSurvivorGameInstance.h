// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MobSurvivorGameInstance.generated.h"

class UDefaultParametersData;
class UMobSurvivorSaveGame;
/**
 * 
 */
UCLASS(ABSTRACT)
class PROGGAMEPLAYPROTO_API UMobSurvivorGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMobSurvivorGameInstance();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveSettings")
	FString SaveName;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "SaveSettings")
	TSubclassOf<UMobSurvivorSaveGame> SaveGameReference;

	UPROPERTY(BlueprintReadWrite, Category = "SaveSettings")
	UMobSurvivorSaveGame* SaveGameInstance;
};
