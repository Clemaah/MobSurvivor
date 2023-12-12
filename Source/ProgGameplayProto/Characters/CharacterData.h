// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterCharacteristics.h"
#include "Engine/DataAsset.h"
#include "CharacterData.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct PROGGAMEPLAYPROTO_API FCharacterLevel
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCharacterCharacteristics Characteristics;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (ClampMin = 0))
	int Price;
};


UCLASS(BlueprintType)
class PROGGAMEPLAYPROTO_API UCharacterData : public UPrimaryDataAsset
{

	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meta")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meta", Meta = (MultiLine = true))
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Characteristics", Meta = (EditFixedOrder, ToolTip = "The first level contains base characteristics. Next ones contains modifiers."))
	TArray<FCharacterLevel> Levels;

	UCharacterData();

	UFUNCTION(BlueprintPure)
	TMap<FString, float> GetCumulativeLevelsMap(const int Level);

	UFUNCTION(BlueprintPure)
	TMap<FString, float> GetLevelMap(const int Level);

	UFUNCTION(BlueprintPure)
	FCharacterCharacteristics GetCumulativeLevelsCharacteristics(const int Level);

	UFUNCTION(BlueprintPure)
	int GetLevelPrice(const int Level);

protected:
	static TMap<FString, float> GetMap(const FCharacterCharacteristics& Characteristics, const int Level);
};
