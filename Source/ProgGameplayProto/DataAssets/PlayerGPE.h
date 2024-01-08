// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerGPE.generated.h"

USTRUCT(BlueprintType)
struct PROGGAMEPLAYPROTO_API FDisplayableCharacteristic
{
	GENERATED_BODY()

	FDisplayableCharacteristic() { };

	FDisplayableCharacteristic(const FText& InName, const float InCurrentValue, const float InNextLevelBonus)
		:Name(InName), CurrentValue(InCurrentValue), NextLevelBonuses(InNextLevelBonus) { };

	UPROPERTY(BlueprintReadOnly)
	FText Name;

	UPROPERTY(BlueprintReadOnly)
	float CurrentValue;

	UPROPERTY(BlueprintReadOnly)
	float NextLevelBonuses;
};


UINTERFACE(Blueprintable, MinimalAPI)
class UPlayerGPE : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROGGAMEPLAYPROTO_API IPlayerGPE
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	TArray<FDisplayableCharacteristic> GetDisplayableCharacteristics(const int Level);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	int GetLevelPrice(const int Level);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	FText GetName();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	FText GetDescription();
};
