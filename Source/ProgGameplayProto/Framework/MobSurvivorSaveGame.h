// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ProgGameplayProto/StartDatas.h"
#include "UObject/ObjectMacros.h"

#include "MobSurvivorSaveGame.generated.h"

class UProjectileData;
class UWeaponData;
class UCharacterData;
/**
 * 
 */
UCLASS()
class PROGGAMEPLAYPROTO_API UMobSurvivorSaveGame : public USaveGame
{
	GENERATED_BODY()

	UMobSurvivorSaveGame();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StartParameters", Meta = (ShowOnlyInnerProperties))
	FMobSurvivorParameters ParametersToSave;
};