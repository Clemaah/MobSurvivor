// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ProgGameplayProto/System/MobSurvivorParameters.h"
#include "DefaultParametersData.generated.h"

class UCharacterData;
class UWeaponData;
class UProjectileData;
/**
 * 
 */
UCLASS()
class PROGGAMEPLAYPROTO_API UDefaultParametersData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StartParameters", Meta = (ShowOnlyInnerProperties))
	FMobSurvivorParameters Parameters;
};
