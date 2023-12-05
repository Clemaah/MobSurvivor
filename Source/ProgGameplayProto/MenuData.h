// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MenuData.generated.h"

class UCharacterData;
class UWeaponData;
class UProjectileData;
/**
 * 
 */
UCLASS()
class PROGGAMEPLAYPROTO_API UMenuData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<UCharacterData*, int> CharactersLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<UWeaponData*, int> WeaponsLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<UProjectileData*, int> ProjectilesLevel;
};
