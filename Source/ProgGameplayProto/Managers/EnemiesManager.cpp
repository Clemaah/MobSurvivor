// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemiesManager.h"

#include "ProgGameplayProto/EnemySpawnRule.h"
#include "ProgGameplayProto/LevelData.h"
#include "ProgGameplayProto/System/GameUtils.h"
#include "ProgGameplayProto/System/MobSurvivorGameMode.h"
#include "ProgGameplayProto/Characters/ProgGameplayProtoCharacter.h"

AEnemiesManager::AEnemiesManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemiesManager::BeginPlay()
{
	Super::BeginPlay();

	GameMode = UGameUtils::GetGameMode(GetWorld());

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

	for (int i = DeadEnemiesList.Num() - 1; i >= 0; i--)
	{
		DestroyEnemy(DeadEnemiesList[i]);
	}

	MoveEnemies(DeltaSeconds);

	EvaluatePunctualRules();

	EvaluateRangeRules(DeltaSeconds);
}

void AEnemiesManager::MoveEnemies(float DeltaSeconds)
{
	const AProgGameplayProtoCharacter* player = UGameUtils::GetMainCharacter();

	if (!IsValid(player)) return;

	FVector playerPosition = player->GetActorLocation();

	for (AEnemy* Enemy : AliveEnemiesList)
	{
		Enemy->Move(DeltaSeconds, playerPosition);
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
	if (GameMode->GetGameTime() >= Rule.Time)
	{
		const FVector clusterLocation = GetSpawnLocation();
		FVector spawnLocation;

		for (int32 i = 0; i < Rule.Number; i++)
		{
			if(Rule.IsACluster)
			{
				const FVector offset = FVector(FMath::FRandRange(-500.0f, 500.0f), FMath::FRandRange(-500.0f, 500.0f), 0);
				spawnLocation = clusterLocation + offset;
			}

			else
				spawnLocation = GetSpawnLocation();

			SpawnEnemy(Rule.Enemy, spawnLocation);
		}

		return true;
	}

	return false;
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
			const FVector spawnLocation = GetSpawnLocation();
			SpawnEnemy(Rule.Enemy, spawnLocation);

			Rule.NumberOfEnemyToSpawn -= 1;
		}
	}

	return false;
}

void AEnemiesManager::SpawnEnemy(TSubclassOf<AEnemy> EnemyClass, FVector SpawnLocation)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
	AEnemy* newEnemy = GetWorld()->SpawnActor<AEnemy>(EnemyClass, SpawnLocation, FRotator::ZeroRotator, SpawnInfo);

	if(!IsValid(newEnemy))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("No Enemy !"));
		return;
	}

	const AProgGameplayProtoCharacter* player = UGameUtils::GetMainCharacter();

	if (!IsValid(player)) return;

	FVector playerPosition = player->GetActorLocation();

	newEnemy->ChangeDirection(playerPosition);
	AliveEnemiesList.Add(newEnemy);

	newEnemy->DieDelegate.AddDynamic(this, &AEnemiesManager::AddEnemyToDeadList);
}

void AEnemiesManager::AddEnemyToDeadList(AEnemy* Enemy)
{
	DeadEnemiesList.Add(Enemy);
}

void AEnemiesManager::DestroyEnemy(AEnemy* Enemy)
{
	GameMode->ChangeGamePointsBy(Enemy->EnemyData->Points);

	DeadEnemiesList.RemoveSwap(Enemy);
	AliveEnemiesList.RemoveSwap(Enemy);

	Enemy->Destroy();
}

FVector AEnemiesManager::GetSpawnLocation()
{
	AActor* mainCharacter = UGameUtils::GetMainCharacter();

	if (!IsValid(mainCharacter)) return FVector::ZeroVector;

	FVector direction = FVector::ForwardVector;
	direction = direction.RotateAngleAxis(FMath::FRandRange(0.0f, 360.0f), FVector::UpVector);

	FVector offset = direction * 2000;
	FVector output = mainCharacter->GetActorLocation() + offset;

	return output;
}