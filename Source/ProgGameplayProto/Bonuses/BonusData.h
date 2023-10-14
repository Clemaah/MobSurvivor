// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BonusData.generated.h"

class UProjectileEffect;
class AProgGameplayProtoCharacter;
class UWeaponComponent;
/**
 *
 */

UCLASS(BlueprintType)
class PROGGAMEPLAYPROTO_API UBonusData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = true))
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<UProjectileEffect>> Effects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BonusFireRate = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BonusFireRateMultiplier = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BonusNumberOfShots = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BonusNumberOfShotsMultiplier = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BonusPrecision = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BonusPrecisionMultiplier = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BonusSpread = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BonusSpreadMultiplier = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BonusDamages = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BonusDamagesMultiplier = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BonusProjectileSize = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BonusProjectileSizeMultiplier = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BonusRange = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BonusRangeMultiplier = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BonusProjectileSpeed = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BonusProjectileSpeedMultiplier = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BonusCriticalHitChance = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BonusCriticalHitChanceMultiplier = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BonusCriticalHitDamageMultiplier = 0;

public:
	UFUNCTION(BlueprintCallable)
	virtual void ApplyOnMainCharacter();

	virtual void Apply(AProgGameplayProtoCharacter* Character, UWeaponComponent* Weapon);

	virtual void ApplyEffects(AProgGameplayProtoCharacter* Character, UWeaponComponent* Weapon);
};
