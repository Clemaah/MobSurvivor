// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawnerManager.h"

#include "ProgGameplayProto/EnemySpawnRule.h"
#include "ProgGameplayProto/LevelData.h"
#include "ProgGameplayProto/System/GameUtils.h"
#include "ProgGameplayProto/System/MobSurvivorGameMode.h"
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
	if (GameMode->GetGameTime() >= Rule.Time)
	{
		if (Rule.Enemy->GetDefaultObject<AEnemy>()->EnemyData->EnemyType == EEnemyType::Weak)
		{
			AActor* mainCharacter = UGameUtils::GetMainCharacter();
			if (!IsValid(mainCharacter))
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("No Character !"));
				return false;
			}

			const FVector ClusterSpawnLocation = GetSpawnLocation();
			FVector ClusterMovementDirection = mainCharacter->GetActorLocation() - ClusterSpawnLocation;
			ClusterMovementDirection.Z = 0;
			ClusterMovementDirection.Normalize();

			//if (ClusterMovementDirection == mainCharacter->GetActorLocation())
			//	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("BBBB !"));

			for (int32 i = 0; i < Rule.Number; i++)
			{
				SpawnEnemyInCluster(Rule.Enemy, ClusterSpawnLocation, ClusterMovementDirection);
			}
		}
		else
		{
			for (int32 i = 0; i < Rule.Number; i++)
			{
				SpawnEnemy(Rule.Enemy);
			}
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
	float minTime = 0;
	float maxTime = 0;
	Rule.SpawnCurve.GetRichCurve()->GetTimeRange(minTime, maxTime);

	if (GameMode->GetGameTime() > maxTime) return true;

	if (GameMode->GetGameTime() >= minTime)
	{
		float currentAmount = Rule.SpawnCurve.GetRichCurve()->Eval(GameMode->GetGameTime());

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

void AEnemySpawnerManager::SpawnEnemyInCluster(TSubclassOf<AEnemy> EnemyClass, FVector ClusterSpawnLocation, FVector ClusterMovementDirection)
{
	const FVector spawnLocation = GetSpawnLocationForCluster(ClusterSpawnLocation);

	lastEnemySpawned = GetWorld()->SpawnActor<AEnemy>(EnemyClass, spawnLocation, FRotator::ZeroRotator);

	if (lastEnemySpawned == nullptr)
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("AAAAAAAAAAAAAAAA !"));
	else lastEnemySpawned->ClusterMovementDirection = ClusterMovementDirection;
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

FVector AEnemySpawnerManager::GetSpawnLocationForCluster(FVector ClusterSpawnLocation)
{

	FVector direction = FVector::ForwardVector;
	direction = direction.RotateAngleAxis(FMath::FRandRange(0.0f, 360.0f), FVector::UpVector);

	FVector offset = direction * FMath::FRandRange(100.0f, 400.0f);
	FVector output = ClusterSpawnLocation + offset;

	return output;
}