// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemiesManager.h"

#include "EnemySpawnRule.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProgGameplayProto/Actors/Enemy.h"
#include "ProgGameplayProto/Actors/MobSurvivorCharacter.h"
#include "ProgGameplayProto/DataAssets/Enemies/EnemyData.h"
#include "ProgGameplayProto/System/GameUtils.h"
#include "ProgGameplayProto/System/MobSurvivorGameMode.h"

AEnemiesManager::AEnemiesManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemiesManager::BeginPlay()
{
	Super::BeginPlay();

	GameMode = UGameUtils::GetGameMode(GetWorld());
	Player = UGameUtils::GetMainCharacter();
	AddTickPrerequisiteActor(Player);

	PlayerPosition = Player->GetActorLocation();
	PlayerPosition.Z = 0;

	LoadSpawnRules();
}

void AEnemiesManager::LoadSpawnRules()
{
	ULevelData* gameLevelData = GameMode->GameLevelData;

	if (!IsValid(gameLevelData)) return;

	PunctualEnemySpawnRules = gameLevelData->PunctualSpawnRules;
	RangeEnemySpawnRules = gameLevelData->RangeSpawnRules;
}

void AEnemiesManager::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	PlayerPosition = Player->GetActorLocation();
	PlayerPosition.Z = 0;

	for (int i = DeadEnemiesList.Num() - 1; i >= 0; i--)
		DestroyEnemy(DeadEnemiesList[i]);

	MoveEnemies(DeltaSeconds);

	EvaluatePunctualRules();

	EvaluateRangeRules(DeltaSeconds);
}

void AEnemiesManager::MoveEnemies(float DeltaSeconds)
{
	for (AEnemy* Enemy : AliveEnemiesList)
	{
		Enemy->Behave(DeltaSeconds, PlayerPosition);

		if (Enemy->DistanceFromPlayerSqrd < DespawnDistanceThresholdSqrd) continue;

		if (!Enemy->GetEnemyCharacteristics().IsTargetingPlayer)
		{
			AddEnemyToDeadList(Enemy, false);
			continue;
		}

		FVector respawnLocation;
		FRotator respawnRotation;

		do {
			respawnLocation = GetSpawnLocation(PlayerPosition, SpawnDistance, SpawnDistance);
			respawnRotation = UKismetMathLibrary::FindLookAtRotation(respawnLocation, PlayerPosition);

		} while (!Enemy->TeleportTo(respawnLocation, respawnRotation));

		Enemy->DistanceFromPlayerSqrd = UKismetMathLibrary::Vector_DistanceSquared(respawnLocation, PlayerPosition);
	}
}

void AEnemiesManager::EvaluatePunctualRules()
{
	for (int32 i = PunctualEnemySpawnRules.Num() - 1; i >= 0; i--)
	{
		bool shouldRemove = EvaluatePunctualRule(PunctualEnemySpawnRules[i]);

		if (shouldRemove)
			PunctualEnemySpawnRules.RemoveAt(i);
	}
}

bool AEnemiesManager::EvaluatePunctualRule(FPunctualEnemySpawnRule Rule)
{
	if (GameMode->GetGameTime() < Rule.Time)
		return false;

	FVector spawnLocation;

	if (Rule.IsACluster)
	{
		const FVector clusterLocation = GetSpawnLocation(PlayerPosition, SpawnDistance, SpawnDistance);
		const FRotator clusterRotation = UKismetMathLibrary::FindLookAtRotation(clusterLocation, PlayerPosition);

		for (int32 i = 0; i < Rule.Number; i++)
		{
			spawnLocation = GetSpawnLocation(clusterLocation, 0, Rule.ClusterRanger);

			SpawnEnemy(Rule.Enemy, spawnLocation, clusterRotation);
		}

		return true;
	}

	for (int32 i = 0; i < Rule.Number; i++)
	{
		spawnLocation = GetSpawnLocation(PlayerPosition, SpawnDistance, SpawnDistance);
		FRotator spawnRotation = UKismetMathLibrary::FindLookAtRotation(spawnLocation, PlayerPosition);

		SpawnEnemy(Rule.Enemy, spawnLocation, spawnRotation);
	}
	return true;
}

void AEnemiesManager::EvaluateRangeRules(float DeltaTime)
{
	for (int32 i = RangeEnemySpawnRules.Num() - 1; i >= 0; i--)
	{
		bool shouldRemove = EvaluateRangeRule(DeltaTime, RangeEnemySpawnRules[i]);

		if (shouldRemove)
			RangeEnemySpawnRules.RemoveAt(i);
	}
}

bool AEnemiesManager::EvaluateRangeRule(float DeltaTime, FRangeEnemySpawnRule& Rule)
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
			const FVector spawnLocation = GetSpawnLocation(PlayerPosition, SpawnDistance, SpawnDistance);
			const FRotator spawnRotation = UKismetMathLibrary::FindLookAtRotation(spawnLocation, PlayerPosition);

			SpawnEnemy(Rule.Enemy, spawnLocation, spawnRotation);

			Rule.NumberOfEnemyToSpawn -= 1;
		}
	}

	return false;
}

void AEnemiesManager::SpawnEnemy(TSubclassOf<AEnemy> EnemyClass, FVector SpawnLocation, FRotator SpawnRotation)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	AEnemy* newEnemy = GetWorld()->SpawnActor<AEnemy>(EnemyClass, SpawnLocation, SpawnRotation, SpawnInfo);

	if(!IsValid(newEnemy))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("Collision !")));

		return;
	}

	newEnemy->DistanceFromPlayerSqrd = UKismetMathLibrary::Vector_DistanceSquared(SpawnLocation, PlayerPosition);
	AliveEnemiesList.Add(newEnemy);

	newEnemy->DieDelegate.AddDynamic(this, &AEnemiesManager::AddEnemyToDeadList);
}

void AEnemiesManager::AddEnemyToDeadList(AEnemy* Enemy, bool bIsGettingPoints)
{
	if (bIsGettingPoints)
		GameMode->ChangeGamePointsBy(Enemy->GetEnemyCharacteristics().Points);

	DeadEnemiesList.Add(Enemy);
}

void AEnemiesManager::DestroyEnemy(AEnemy* Enemy)
{
	DeadEnemiesList.RemoveSwap(Enemy);
	AliveEnemiesList.RemoveSwap(Enemy);

	Enemy->Destroy();
}

FVector AEnemiesManager::GetSpawnLocation(FVector Center, float MinOffset, float MaxOffset)
{
	FVector direction = FVector::ForwardVector;
	direction = direction.RotateAngleAxis(FMath::FRandRange(0.0f, 360.0f), FVector::UpVector);

	FVector offset = direction * FMath::FRandRange(MinOffset, MaxOffset);
	FVector output = Center + offset;

	return output;
}