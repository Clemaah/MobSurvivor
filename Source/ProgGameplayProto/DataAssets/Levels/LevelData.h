// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelData.generated.h"

class UBonusData;
struct FRangeEnemySpawnRule;
struct FPunctualEnemySpawnRule;

/**
 *
 */
UCLASS(BlueprintType)
class PROGGAMEPLAYPROTO_API ULevelData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	int Duration;

	UPROPERTY(EditAnywhere)
	TArray<FPunctualEnemySpawnRule> PunctualSpawnRules;

	UPROPERTY(EditAnywhere)
	TArray<FRangeEnemySpawnRule> RangeSpawnRules;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UBonusData*> Bonuses;
};
