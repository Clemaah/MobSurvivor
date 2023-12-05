// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterData.generated.h"

/**
 * 
 */

struct FCharacterCharacteristics;

UCLASS(BlueprintType)
class PROGGAMEPLAYPROTO_API UCharacterData : public UPrimaryDataAsset
{

	GENERATED_BODY()

public:
	UCharacterData();

	UFUNCTION(BlueprintCallable)
	TMap<FString, float> GetMap(const int Level);

	UFUNCTION(BlueprintCallable)
	FCharacterCharacteristics GetLevelCharacteristics(const int Level);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meta")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meta", Meta = (MultiLine = true))
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, EditFixedSize, Category = "Characteristics", Meta = (EditFixedOrder, ToolTip = "The first level contains base characteristics. Next ones contains modifiers."))
	TArray<FCharacterCharacteristics> Levels;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, EditFixedSize, Category = "Characteristics", Meta = (EditFixedOrder))
	TArray<int> LevelsPrice;
};
