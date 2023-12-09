// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProgGameplayProto/System/MobSurvivorSaveGame.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameUtils.generated.h"

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
	UFUNCTION(BlueprintPure, Category = "Manager")
	static AProgGameplayProtoCharacter* GetMainCharacter();

	UFUNCTION(BlueprintPure, Category = "Manager")
	static UMobSurvivorSaveGame* GetSaveGame(UWorld* World);
};
