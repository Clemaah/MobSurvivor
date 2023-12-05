// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponCharacteristics.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct PROGGAMEPLAYPROTO_API FWeaponCharacteristics
{
	GENERATED_BODY()

	FWeaponCharacteristics()
	{
		FireRate = 0;
		Precision = 0;
		Spread = 0;
		DoubleShotChance = 0;
		ShotsNumber = 0;
		DamagesMultiplier = 0;
		RangeMultiplier = 0;
		ProjectileSizeMultiplier = 0;
		ProjectileSpeedMultiplier = 0;
		CriticalHitChanceMultiplier = 0;
	}

	FWeaponCharacteristics& operator+=(const FWeaponCharacteristics& Other)
	{
		FireRate += Other.FireRate;
		Precision += Other.Precision;
		Spread += Other.Spread;
		DoubleShotChance += Other.DoubleShotChance;
		ShotsNumber += Other.ShotsNumber;
		DamagesMultiplier += Other.DamagesMultiplier;
		RangeMultiplier += Other.RangeMultiplier;
		ProjectileSizeMultiplier += Other.ProjectileSizeMultiplier;
		ProjectileSpeedMultiplier += Other.ProjectileSpeedMultiplier;
		CriticalHitChanceMultiplier += Other.CriticalHitChanceMultiplier;

		return *this;
	}

	friend FWeaponCharacteristics operator+(FWeaponCharacteristics One, const FWeaponCharacteristics& Other)
	{
		One += Other;
		return One;
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|General")
	float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|General")
	float Precision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|General")
	float Spread;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Salvo")
	float DoubleShotChance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Salvo")
	int ShotsNumber;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Projectile Multipliers")
	float DamagesMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Projectile Multipliers")
	float RangeMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Projectile Multipliers")
	float ProjectileSizeMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Projectile Multipliers")
	float ProjectileSpeedMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Projectile Multipliers")
	float CriticalHitChanceMultiplier;
};