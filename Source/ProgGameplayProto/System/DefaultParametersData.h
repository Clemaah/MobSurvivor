// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	int TotalCoins;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	int TotalPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	FString PlayerToken;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	TMap<UCharacterData*, int> CharactersCurrentLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	TMap<UWeaponData*, int> WeaponsCurrentLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	TMap<UProjectileData*, int> ProjectilesCurrentLevel;
};