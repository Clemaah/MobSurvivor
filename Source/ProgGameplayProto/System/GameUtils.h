// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProgGameplayProto/System/MobSurvivorSaveGame.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameUtils.generated.h"

class AMobSurvivorGameMode;
class UMobSurvivorGameInstance;
class UMobSurvivorSaveGame;
class AProgGameplayProtoCharacter;

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
	static AProgGameplayProtoCharacter* GetMainCharacter();

	UFUNCTION(BlueprintPure, Category = "MobSurvivor|Manager")
	static UMobSurvivorGameInstance* GetGameInstance(const UWorld* World);

	UFUNCTION(BlueprintPure, Category = "MobSurvivor|Manager")
	static AMobSurvivorGameMode* GetGameMode(const UWorld* World);

	UFUNCTION(BlueprintPure, Category = "MobSurvivor|Manager")
	static bool IsAValidEmail(const FString& Email);
};
