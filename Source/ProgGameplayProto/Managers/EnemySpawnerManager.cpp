// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawnerManager.h"

#include "ProgGameplayProto/EnemySpawnRule.h"
#include "ProgGameplayProto/LevelData.h"
#include "ProgGameplayProto/System/GameUtils.h"
#include "ProgGameplayProto/System/MobSurvivorGameMode.h"
#include "ProgGameplayProto/System/MobSurvivorGameState.h"
#include "ProgGameplayProto/Characters/ProgGameplayProtoCharacter.h"
#include "Kismet/GameplayStatics.h"

AEnemySpawnerManager::AEnemySpawnerManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemySpawnerManager::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	EvaluatePunctualRules();

	EvaluateRangeRules(DeltaSeconds);
}

void AEnemySpawnerManager::BeginPlay()
{
	Super::BeginPlay();

	LoadSpawnRules();
}

void AEnemySpawnerManager::LoadSpawnRules()
{
	GameMode = Cast<AMobSurvivorGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GameState = GameMode->GetGameState<AMobSurvivorGameState>();

	ULevelData* gameLevelData = GameMode->GameLevelData;

	if (!IsValid(gameLevelData)) return;

	PunctualEnemySpawnRules = gameLevelData->PunctualSpawnRules;
	RangeEnemySpawnRules = gameLevelData->RangeSpawnRules;
}

void AEnemySpawnerManager::EvaluatePunctualRules()
{
	for (int32 i = PunctualEnemySpawnRules.Num() - 1; i >= 0; i--)
	{
		bool shouldRemove = EvaluatePunctualRule(PunctualEnemySpawnRules[i]);

		if (shouldRemove)
			PunctualEnemySpawnRules.RemoveAt(i);
	}
}

bool AEnemySpawnerManager::EvaluatePunctualRule(FPunctualEnemySpawnRule Rule)
{
	if (GameState->GetGameTime() >= Rule.Time)
	{
		for (int32 i = 0; i < Rule.Number; i++)
		{
			SpawnEnemy(Rule.Enemy);
		}

		return true;
	}

	return false;
}

void AEnemySpawnerManager::EvaluateRangeRules(float DeltaTime)
{
	for (int32 i = RangeEnemySpawnRules.Num() - 1; i >= 0; i--)
	{
		bool shouldRemove = EvaluateRangeRule(DeltaTime, RangeEnemySpawnRules[i]);

		if (shouldRemove)
			RangeEnemySpawnRules.RemoveAt(i);
	}
}

bool AEnemySpawnerManager::EvaluateRangeRule(float DeltaTime, FRangeEnemySpawnRule& Rule)
{
	AMobSurvivorGameState* gameState = GameMode->GetGameState<AMobSurvivorGameState>();

	float minTime = 0;
	float maxTime = 0;
	Rule.SpawnCurve.GetRichCurve()->GetTimeRange(minTime, maxTime);

	if (gameState->GetGameTime() > maxTime) return true;

	if (gameState->GetGameTime() >= minTime)
	{
		float currentAmount = Rule.SpawnCurve.GetRichCurve()->Eval(gameState->GetGameTime());

		Rule.NumberOfEnemyToSpawn += currentAmount * DeltaTime;

		while (Rule.NumberOfEnemyToSpawn > 1)
		{
			SpawnEnemy(Rule.Enemy);

			Rule.NumberOfEnemyToSpawn -= 1;
		}
	}

	return false;
}

void AEnemySpawnerManager::SpawnEnemy(TSubclassOf<AEnemy> EnemyClass)
{
	const FVector spawnLocation = GetSpawnLocation();

	GetWorld()->SpawnActor<AEnemy>(EnemyClass, spawnLocation, FRotator::ZeroRotator);
}

FVector AEnemySpawnerManager::GetSpawnLocation()
{
	AActor* mainCharacter = UGameUtils::GetMainCharacter();

	if (!IsValid(mainCharacter)) return FVector::ZeroVector;

	FVector direction = FVector::ForwardVector;
	direction = direction.RotateAngleAxis(FMath::FRandRange(0.0f, 360.0f), FVector::UpVector);

	FVector offset = direction * 2000;
	FVector output = mainCharacter->GetActorLocation() + offset;

	return output;
}