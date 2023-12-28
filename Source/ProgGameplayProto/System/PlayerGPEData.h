// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PlayerGPEData.generated.h"

class UPersonaData;
class UWeaponData;
class UProjectileData;
/**
 *
 */
UCLASS()
class PROGGAMEPLAYPROTO_API UPlayerGPEData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	TArray<UPersonaData*> Personas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	TArray<UWeaponData*> Weapons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	TArray<UProjectileData*> Projectiles;
};