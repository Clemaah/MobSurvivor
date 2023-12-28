#pragma once

#include "CoreMinimal.h"
#include "Enemies/Enemy.h"
#include "EnemySpawnRule.generated.h"

USTRUCT()
struct FPunctualEnemySpawnRule
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float Time = 0;

	UPROPERTY(EditAnywhere)
	int32 Number = 0;

	UPROPERTY(EditAnywhere)
	bool IsACluster = false;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AEnemy> Enemy;
};

USTRUCT()
struct FRangeEnemySpawnRule
{
	GENERATED_BODY()

public:
	// spawn value of enemy according to time
	UPROPERTY(EditAnywhere)
	FRuntimeFloatCurve SpawnCurve;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AEnemy> Enemy;

	UPROPERTY()
	float NumberOfEnemyToSpawn = 0;
};
