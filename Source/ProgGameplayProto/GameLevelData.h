// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameLevelData.generated.h"

class UBonusData;
struct FRangeEnemySpawnRule;
struct FPunctualEnemySpawnRule;

/**
 *
 */
UCLASS(BlueprintType)
class PROGGAMEPLAYPROTO_API UGameLevelData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<FPunctualEnemySpawnRule> PunctualSpawnRules;

	UPROPERTY(EditAnywhere)
	TArray<FRangeEnemySpawnRule> RangeSpawnRules;

	UPROPERTY(EditAnywhere)
	TArray<UBonusData*> Bonuses;
};
