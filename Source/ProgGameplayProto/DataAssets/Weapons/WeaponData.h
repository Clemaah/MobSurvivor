// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "WeaponCharacteristics.h"
#include "ProgGameplayProto/DataAssets/PlayerGPE.h"

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
class PROGGAMEPLAYPROTO_API UWeaponData : public UDataAsset, public IPlayerGPE
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

	UFUNCTION(BlueprintCallable)
	virtual TArray<FDisplayableCharacteristic> GetDisplayableCharacteristics_Implementation(const int Level) override;

	UFUNCTION(BlueprintCallable)
	virtual int GetLevelPrice_Implementation(const int Level) override;

	UFUNCTION(BlueprintCallable)
	virtual FText GetName_Implementation() override;

	UFUNCTION(BlueprintCallable)
	virtual FText GetDescription_Implementation() override;

	UFUNCTION(BlueprintCallable)
	virtual FWeaponCharacteristics GetCurrentCharacteristics(const int Level);
};
