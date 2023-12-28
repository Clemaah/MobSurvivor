// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "EnemiesManager.generated.h"

class AEnemy;
class AMobSurvivorGameMode;
class AMobSurvivorGameState;
struct FPunctualEnemySpawnRule;
struct FRangeEnemySpawnRule;
/**
 *
 */
UCLASS()
class PROGGAMEPLAYPROTO_API AEnemiesManager : public AInfo
{
	GENERATED_BODY()

public:
	AEnemiesManager();

protected:
	UPROPERTY()
	AMobSurvivorGameMode* GameMode;

	UPROPERTY()
	TArray<FPunctualEnemySpawnRule> PunctualEnemySpawnRules;

	UPROPERTY()
	TArray<FRangeEnemySpawnRule> RangeEnemySpawnRules;

	UPROPERTY()
	TArray<AEnemy*> AliveEnemiesList;

	UPROPERTY()
	TArray<AEnemy*> DeadEnemiesList;

public:
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;
	
	virtual void MoveEnemies(float DeltaSeconds);

	virtual void LoadSpawnRules();

	virtual void EvaluatePunctualRules();

	// returns true if should remove rule after evaluation
	virtual bool EvaluatePunctualRule(FPunctualEnemySpawnRule Rule);

	virtual void EvaluateRangeRules(float DeltaTime);

	// returns true if should remove rule after evaluation
	virtual bool EvaluateRangeRule(float DeltaTime, FRangeEnemySpawnRule& Rule);

	virtual void SpawnEnemy(TSubclassOf<AEnemy> EnemyClass, FVector SpawnLocation);

	UFUNCTION()
	virtual void AddEnemyToDeadList(AEnemy* Enemy);

	virtual void DestroyEnemy(AEnemy* Enemy);

	//virtual void SpawnEnemyInCluster(TSubclassOf<AEnemy> EnemyClass, FVector ClusterSpawnLocation, FVector ClusterMovementDirection);

	virtual FVector GetSpawnLocation();

	//virtual FVector GetSpawnLocationForCluster(FVector ClusterSpawnLocation);
};