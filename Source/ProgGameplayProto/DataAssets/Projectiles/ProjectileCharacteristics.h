// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileCharacteristics.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct PROGGAMEPLAYPROTO_API FProjectileCharacteristics
{
	GENERATED_BODY()

	FProjectileCharacteristics()
	{
		Damages = 0;
		Range = 0;
		Size = 0;
		Speed = 0;
		CriticalHitChance = 0;
		CriticalHitMultiplier = 0;
	}

	FProjectileCharacteristics& operator+=(const FProjectileCharacteristics& Other)
	{
		Damages += Other.Damages;
		Range += Other.Range;
		Size += Other.Size;
		Speed += Other.Speed;
		CriticalHitChance += Other.CriticalHitChance;
		CriticalHitMultiplier += Other.CriticalHitMultiplier;

		return *this;
	}

	friend FProjectileCharacteristics operator+(FProjectileCharacteristics One, const FProjectileCharacteristics& Other)
	{
		One += Other;
		return One;
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	float Damages;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	float Range;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	float Size;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	float CriticalHitChance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	float CriticalHitMultiplier;
};