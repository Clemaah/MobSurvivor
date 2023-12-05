// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ProjectileCharacteristics.h"
#include "ProjectileData.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class PROGGAMEPLAYPROTO_API UProjectileData : public UDataAsset
{
	GENERATED_BODY()

public:
	UProjectileData();

	UFUNCTION(BlueprintCallable)
	TMap<FString, float> GetMap(const int Level);

	UFUNCTION(BlueprintCallable)
	FProjectileCharacteristics GetLevelCharacteristics(const int Level);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meta")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meta", Meta = (MultiLine = true))
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, EditFixedSize, Category = "Characteristics", Meta = (EditFixedOrder, ToolTip = "The first level contains base characteristics. Next ones contains modifiers."))
	TArray<FProjectileCharacteristics> Levels;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, EditFixedSize, Category = "Characteristics", Meta = (EditFixedOrder))
	TArray<int> LevelsPrice;
};
