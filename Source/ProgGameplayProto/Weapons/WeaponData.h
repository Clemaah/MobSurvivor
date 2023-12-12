// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponCharacteristics.h"
#include "Engine/DataAsset.h"
#include "WeaponData.generated.h"

/**
 *
 */

USTRUCT(BlueprintType)
struct PROGGAMEPLAYPROTO_API FWeaponLevel
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FWeaponCharacteristics Characteristics;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (ClampMin = 0))
	int Price;
};


UCLASS(BlueprintType)
class PROGGAMEPLAYPROTO_API UWeaponData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meta")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meta", Meta = (MultiLine = true))
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Characteristics", Meta = (EditFixedOrder, ToolTip = "The first level contains base characteristics. Next ones contains modifiers."))
	TArray<FWeaponLevel> Levels;

	UWeaponData();

	UFUNCTION(BlueprintPure)
	TMap<FString, float> GetCumulativeLevelsMap(const int Level);

	UFUNCTION(BlueprintPure)
	TMap<FString, float> GetLevelMap(const int Level);

	UFUNCTION(BlueprintPure)
	FWeaponCharacteristics GetCumulativeLevelsCharacteristics(const int Level);

	UFUNCTION(BlueprintPure)
	int GetLevelPrice(const int Level);

protected:
	static TMap<FString, float> GetMap(const FWeaponCharacteristics& Characteristics, const int Level);
};
