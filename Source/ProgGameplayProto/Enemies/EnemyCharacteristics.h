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
		Health = 0;
		Speed = 0;
	}

	FEnemyCharacteristics& operator+=(const FEnemyCharacteristics& Other)
	{
		Health += Other.Health;
		Speed += Other.Speed;

		return *this;
	}

	friend FEnemyCharacteristics operator+(FEnemyCharacteristics One, const FEnemyCharacteristics& Other)
	{
		One += Other;
		return One;
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy|Health")
		float Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy|Movement")
		float Speed;

};
