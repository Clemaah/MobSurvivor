// Copyright Epic Games, Inc. All Rights Reserved.

#include "MobSurvivorGameMode.h"

#include "ProgGameplayProto/Managers/EnemySpawnerManager.h"
#include "ProgGameplayProto/Managers/BonusManager.h"
#include "UObject/ConstructorHelpers.h"


void AMobSurvivorGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	EnemySpawnerManager = GetWorld()->SpawnActor<AEnemySpawnerManager>();
	BonusManager = GetWorld()->SpawnActor<ABonusManager>();
}