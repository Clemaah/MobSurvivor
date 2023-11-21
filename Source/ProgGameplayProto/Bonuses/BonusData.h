// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BonusData.generated.h"

class UProjectileEffect;
class AProgGameplayProtoCharacter;
class UWeaponComponent;
class UPersonaComponent;
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	float BonusFireRate = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	float BonusFireRateMultiplier = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	float BonusNumberOfShots = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	float BonusNumberOfShotsMultiplier = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	float BonusPrecision = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	float BonusPrecisionMultiplier = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	float BonusSpread = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	float BonusSpreadMultiplier = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	float BonusDamages = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	float BonusDamagesMultiplier = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Projectile")
	float BonusProjectileSize = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Projectile")
	float BonusProjectileSizeMultiplier = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Projectile")
	float BonusRange = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Projectile")
	float BonusRangeMultiplier = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Projectile")
	float BonusProjectileSpeed = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Projectile")
	float BonusProjectileSpeedMultiplier = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Criticals")
	float BonusCriticalHitChance = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Criticals")
	float BonusCriticalHitChanceMultiplier = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Criticals")
	float BonusCriticalHitDamageMultiplier = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Persona Data|Health")
	float BonusMaxHealth = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Persona Data|Health")
	float BonusRegenerationRate = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Persona Data|Drop")
	float BonusDropChance = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Persona Data|Drop")
	float BonusDropCollectorRadius = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Persona Data|Drop")
	float BonusCoinMultiplier = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Persona Data|Drop")
	float BonusExperienceMultiplier = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Persona Data|Upgrade")
	int BonusNumberOfUpgrades = 0;

public:
	UFUNCTION(BlueprintCallable)
	virtual void ApplyOnMainCharacter();

	virtual void Apply(AProgGameplayProtoCharacter* Character, UWeaponComponent* Weapon, UPersonaComponent* Persona);

	virtual void ApplyEffects(AProgGameplayProtoCharacter* Character, UWeaponComponent* Weapon);
};
