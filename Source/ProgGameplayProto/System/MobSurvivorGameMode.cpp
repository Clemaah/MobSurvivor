// Copyright Epic Games, Inc. All Rights Reserved.

#include "MobSurvivorGameMode.h"

#include "ProgGameplayProto/LevelData.h"
#include "ProgGameplayProto/Managers/EnemySpawnerManager.h"
#include "ProgGameplayProto/Managers/BonusManager.h"
#include "UObject/ConstructorHelpers.h"


AMobSurvivorGameMode::AMobSurvivorGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMobSurvivorGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	EnemySpawnerManager = GetWorld()->SpawnActor<AEnemySpawnerManager>();
	BonusManager = GetWorld()->SpawnActor<ABonusManager>();
}


void AMobSurvivorGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GameTime >= GameLevelData->Duration)
	{
		OnWin();
		return;
	}
		
	GameTime += DeltaSeconds;



	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, "Game Time: " + FString::SanitizeFloat(GameTime));
}