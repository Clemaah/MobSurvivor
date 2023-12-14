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
		FireRate = 0;
	}

	FEnemyCharacteristics& operator+=(const FEnemyCharacteristics& Other)
	{
		FireRate += Other.FireRate;

		return *this;
	}

	friend FEnemyCharacteristics operator+(FEnemyCharacteristics One, const FEnemyCharacteristics& Other)
	{
		One += Other;
		return One;
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy|General")
		float FireRate;

};
