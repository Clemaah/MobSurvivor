// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ProjectileCharacteristics.h"
#include "ProgGameplayProto/DisplayablePlayerElementInterface.h"
#include "ProjectileData.generated.h"

class UProjectileEffect;
class AProgGameplayProtoCharacter;
class UWeaponComponent;
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
class PROGGAMEPLAYPROTO_API UProjectileData : public UDataAsset, public IDisplayablePlayerElementInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meta")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meta", Meta = (MultiLine = true))
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Characteristics", Meta = (EditFixedOrder, ToolTip = "The first level contains base characteristics. Next ones contains modifiers."))
	TArray<FProjectileLevel> Levels;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Effects")
	TArray<TSubclassOf<UProjectileEffect>> Effects;

	UProjectileData();

	UFUNCTION(BlueprintCallable)
	virtual TArray<FDisplayableCharacteristic> GetDisplayableCharacteristics_Implementation(const int Level) override;

	UFUNCTION(BlueprintCallable)
	virtual int GetLevelPrice_Implementation(const int Level) override;

	UFUNCTION(BlueprintCallable)
	virtual FText GetName_Implementation() override;

	UFUNCTION(BlueprintCallable)
	virtual FText GetDescription_Implementation() override;

	UFUNCTION(BlueprintCallable)
	virtual FProjectileCharacteristics GetCurrentCharacteristics(const int Level);
};
