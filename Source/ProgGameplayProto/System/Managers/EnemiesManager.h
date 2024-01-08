// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "EnemiesManager.generated.h"

class AMobSurvivorCharacter;
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

	TObjectPtr<AMobSurvivorCharacter> Player;

	FVector PlayerPosition;

	float DespawnDistanceThresholdSqrd = 9000000;

	float SpawnDistance = 2000;

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

	virtual void SpawnEnemy(TSubclassOf<AEnemy> EnemyClass, FVector SpawnLocation, FRotator SpawnRotation);

	UFUNCTION()
	virtual void AddEnemyToDeadList(AEnemy* Enemy, bool bIsGettingPoints);

	virtual void DestroyEnemy(AEnemy* Enemy);

	virtual FVector GetSpawnLocation(FVector Center, float MinOffset, float MaxOffset);
};