// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacteristics.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct PROGGAMEPLAYPROTO_API FEnemyCharacteristics
{
	GENERATED_BODY()

	FEnemyCharacteristics()
	{
		Points = 0;
		DistanceToShootSqrd = 0;
		DistanceToRecedeSqrd = 0;
		IsTargetingPlayer = false;
	}

	FEnemyCharacteristics& operator+=(const FEnemyCharacteristics& Other)
	{
		Points += Other.Points;
		DistanceToShootSqrd += Other.DistanceToShootSqrd;
		DistanceToRecedeSqrd += Other.DistanceToRecedeSqrd;
		IsTargetingPlayer = Other.IsTargetingPlayer;

		return *this;
	}

	friend FEnemyCharacteristics operator+(FEnemyCharacteristics One, const FEnemyCharacteristics& Other)
	{
		One += Other;
		return One;
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	int Points;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	float DistanceToShootSqrd;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	float DistanceToRecedeSqrd;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	bool IsTargetingPlayer;
};