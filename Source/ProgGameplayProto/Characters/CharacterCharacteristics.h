// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProgGameplayProto/Characteristics.h"
#include "CharacterCharacteristics.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct PROGGAMEPLAYPROTO_API FCharacterCharacteristics : public FCharacteristics
{
	GENERATED_BODY()

	FCharacterCharacteristics()
	{
		MaxHealth = 0;
		RegenerationRate = 0;
		Speed = 0;
		DropCollectorRadius = 0;
		ExperienceMultiplier = 0;
		CoinMultiplier = 0;
		CoinDropChanceMultiplier = 0;
		UpgradeDropChanceMultiplier = 0;
		UpgradesNumber = 0;
		DoubleShotChanceMultiplier = 0;
		FireRateMultiplier = 0;
		PrecisionMultiplier = 0;
		SpreadMultiplier = 0;
	}

	FCharacterCharacteristics& operator+=(const FCharacterCharacteristics& Other)
	{
		MaxHealth += Other.MaxHealth;
		RegenerationRate += Other.RegenerationRate;
		Speed += Other.Speed;
		DropCollectorRadius += Other.DropCollectorRadius;
		ExperienceMultiplier += Other.ExperienceMultiplier;
		CoinMultiplier += Other.CoinMultiplier;
		CoinDropChanceMultiplier += Other.CoinDropChanceMultiplier;
		UpgradeDropChanceMultiplier += Other.UpgradeDropChanceMultiplier;
		UpgradesNumber += Other.UpgradesNumber;
		DoubleShotChanceMultiplier += Other.DoubleShotChanceMultiplier;
		FireRateMultiplier += Other.FireRateMultiplier;
		PrecisionMultiplier += Other.PrecisionMultiplier;
		SpreadMultiplier += Other.SpreadMultiplier;

		return *this;
	}

	friend FCharacterCharacteristics operator+(FCharacterCharacteristics One, const FCharacterCharacteristics& Other)
	{
		One += Other;
		return One;
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character|Health")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character|Health")
	float RegenerationRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character|Movement")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character|Drops")
	float DropCollectorRadius;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character|Drops")
	float ExperienceMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character|Drops")
	float CoinMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character|Drops")
	float CoinDropChanceMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character|Drops")
	float UpgradeDropChanceMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character|Upgrades")
	int UpgradesNumber;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character|Attack")
	float DoubleShotChanceMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character|Attack")
	float FireRateMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character|Attack")
	float PrecisionMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character|Attack")
	float SpreadMultiplier;
};