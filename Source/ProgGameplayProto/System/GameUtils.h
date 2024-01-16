// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuGameMode.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameUtils.generated.h"

class AMobSurvivorGameMode;
class UMobSurvivorGameInstance;
class UMobSurvivorSaveGame;
class AMobSurvivorCharacter;

/**
 *
 */
UCLASS

()
class PROGGAMEPLAYPROTO_API UGameUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "MobSurvivor|Manager")
	static AMobSurvivorCharacter* GetMainCharacter();

	UFUNCTION(BlueprintPure, Category = "MobSurvivor|Manager")
	static UMobSurvivorGameInstance* GetGameInstance(const UWorld* World);

	UFUNCTION(BlueprintPure, Category = "MobSurvivor|Manager")
	static AMobSurvivorGameMode* GetGameMode(const UWorld* World);

	UFUNCTION(BlueprintPure, Category = "MobSurvivor|Manager")
	static AMenuGameMode* GetMenuGameMode(const UWorld* World);

	UFUNCTION(BlueprintPure, Category = "MobSurvivor|Manager")
	static bool IsAValidEmail(const FString& Email);
};
