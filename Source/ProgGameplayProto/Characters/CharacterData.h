// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterCharacteristics.h"
#include "Engine/DataAsset.h"
#include "ProgGameplayProto/DisplayablePlayerElementInterface.h"
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
class PROGGAMEPLAYPROTO_API UCharacterData : public UPrimaryDataAsset, public IDisplayablePlayerElementInterface
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

	UFUNCTION(BlueprintCallable)
	virtual TArray<FDisplayableCharacteristic> GetDisplayableCharacteristics_Implementation(const int Level) override;

	UFUNCTION(BlueprintCallable)
	virtual int GetLevelPrice_Implementation(const int Level) override;

	UFUNCTION(BlueprintCallable)
	virtual FText GetName_Implementation() override;

	UFUNCTION(BlueprintCallable)
	virtual FText GetDescription_Implementation() override;

	UFUNCTION(BlueprintCallable)
	virtual FCharacterCharacteristics GetCurrentCharacteristics(const int Level);
};
