// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ProjectileCharacteristics.h"
#include "ProjectileData.generated.h"

/**
 *
 */

USTRUCT(BlueprintType)
struct PROGGAMEPLAYPROTO_API FProjectileLevel
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FProjectileCharacteristics Characteristics;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (ClampMin = 0))
	int Price;
};

UCLASS(BlueprintType)
class PROGGAMEPLAYPROTO_API UProjectileData : public UDataAsset
{
	GENERATED_BODY()

public:
	UProjectileData();

	UFUNCTION(BlueprintCallable)
	TMap<FString, float> GetMap(const int Level);

	UFUNCTION(BlueprintCallable)
	FProjectileCharacteristics GetCurrentCharacteristics(const int Level);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meta")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meta", Meta = (MultiLine = true))
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Characteristics", Meta = (EditFixedOrder, ToolTip = "The first level contains base characteristics. Next ones contains modifiers."))
	TArray<FProjectileLevel> Levels;
};
