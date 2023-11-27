// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponData.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class PROGGAMEPLAYPROTO_API UWeaponData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Meta")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Meta", meta = (MultiLine = true))
	FText Description;

	//number of shots / seconds
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	float FireRate = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	float FireRateMultiplier = 1;

	//roudned to nearest integer
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	float NumberOfShots = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	float NumberOfShotsMultiplier = 1;

	//1 is 100% precise, 0 can have a variation of direction up to 30 degrees
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	float Precision = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	float PrecisionMultiplier = 1;

	//spread in degrees, unclamped
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	float Spread;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	float SpreadMultiplier = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	float Damages = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|General")
	float DamagesMultiplier = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Projectile")
	float Range = 700;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Projectile")
	float RangeMultiplier = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Projectile")
	float ProjectileSize = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Projectile")
	float ProjectileSizeMultiplier = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Projectile")
	float ProjectileSpeed = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Projectile")
	float ProjectileSpeedMultiplier = 1;

	//0 is 0%, 1 is 100%
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Criticals")
	float CriticalHitChance = 0.025f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Criticals")
	float CriticalHitChanceMultiplier = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data|Criticals")
	float CriticalHitDamageMultiplier = 2;
};
