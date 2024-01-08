// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterCharacteristics.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct PROGGAMEPLAYPROTO_API FCharacterCharacteristics
{
	GENERATED_BODY()

	FCharacterCharacteristics()
	{
		DropCollectorRadius = 0;
		ExperienceMultiplier = 0;
		CoinMultiplier = 0;
		CoinDropChanceMultiplier = 0;
		UpgradeDropChanceMultiplier = 0;
		UpgradesNumber = 0;
	}

	FCharacterCharacteristics& operator+=(const FCharacterCharacteristics& Other)
	{
		DropCollectorRadius += Other.DropCollectorRadius;
		ExperienceMultiplier += Other.ExperienceMultiplier;
		CoinMultiplier += Other.CoinMultiplier;
		CoinDropChanceMultiplier += Other.CoinDropChanceMultiplier;
		UpgradeDropChanceMultiplier += Other.UpgradeDropChanceMultiplier;
		UpgradesNumber += Other.UpgradesNumber;

		return *this;
	}

	friend FCharacterCharacteristics operator+(FCharacterCharacteristics One, const FCharacterCharacteristics& Other)
	{
		One += Other;
		return One;
	}

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
};