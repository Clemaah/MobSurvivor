// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponCharacteristics.h"
#include "Engine/DataAsset.h"
#include "WeaponData.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class PROGGAMEPLAYPROTO_API UWeaponData : public UDataAsset
{
	GENERATED_BODY()

public:
	UWeaponData();

	UFUNCTION(BlueprintCallable)
	TMap<FString, float> GetMap(const int Level);

	UFUNCTION(BlueprintCallable)
	FWeaponCharacteristics GetLevelCharacteristics(const int Level);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meta")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meta", Meta = (MultiLine = true))
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, EditFixedSize, Category = "Characteristics", Meta = (EditFixedOrder, ToolTip = "The first level contains base characteristics. Next ones contains modifiers."))
	TArray<FWeaponCharacteristics> Levels;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, EditFixedSize, Category = "Characteristics", Meta = (EditFixedOrder))
	TArray<int> LevelsPrice;
};
