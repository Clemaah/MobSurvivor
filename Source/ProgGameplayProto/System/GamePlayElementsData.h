// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GamePlayElementsData.generated.h"

class UCharacterData;
class UWeaponData;
class UProjectileData;
/**
 *
 */
UCLASS()
class PROGGAMEPLAYPROTO_API UGamePlayElementsData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	TArray<UCharacterData*> Characters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	TArray<UWeaponData*> Weapons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	TArray<UProjectileData*> Projectiles;
};