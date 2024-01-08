// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PersonaCharacteristics.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct PROGGAMEPLAYPROTO_API FPersonaCharacteristics
{
	GENERATED_BODY()

	FPersonaCharacteristics()
	{
		MaxHealth = 0;
		RegenerationRate = 0;
		Speed = 0;
		DoubleShotChanceMultiplier = 0;
		FireRateMultiplier = 0;
		PrecisionMultiplier = 0;
		SpreadMultiplier = 0;
	}

	FPersonaCharacteristics& operator+=(const FPersonaCharacteristics& Other)
	{
		MaxHealth += Other.MaxHealth;
		RegenerationRate += Other.RegenerationRate;
		Speed += Other.Speed;
		DoubleShotChanceMultiplier += Other.DoubleShotChanceMultiplier;
		FireRateMultiplier += Other.FireRateMultiplier;
		PrecisionMultiplier += Other.PrecisionMultiplier;
		SpreadMultiplier += Other.SpreadMultiplier;

		return *this;
	}

	friend FPersonaCharacteristics operator+(FPersonaCharacteristics One, const FPersonaCharacteristics& Other)
	{
		One += Other;
		return One;
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Persona|Health")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Persona|Health")
	float RegenerationRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Persona|Movement")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Persona|Attack")
	float DoubleShotChanceMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Persona|Attack")
	float FireRateMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Persona|Attack")
	float PrecisionMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Persona|Attack")
	float SpreadMultiplier;
};