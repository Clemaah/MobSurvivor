// Copyright Epic Games, Inc. All Rights Reserved.

#include "MobSurvivorGameMode.h"

#include "GameUtils.h"
#include "ProgGameplayProto/HealthComponent.h"
#include "ProgGameplayProto/LevelData.h"
#include "ProgGameplayProto/Characters/ProgGameplayProtoCharacter.h"
#include "ProgGameplayProto/Managers/EnemySpawnerManager.h"
#include "ProgGameplayProto/Managers/BonusManager.h"


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

void AMobSurvivorGameMode::BeginPlay()
{
	Super::BeginPlay();

	UGameUtils::GetMainCharacter()->GetHealth()->OnHealthDie.AddDynamic(this, &AMobSurvivorGameMode::OnLoose);
}


void AMobSurvivorGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GameTime >= GameLevelData->Duration)
	{
		OnWin();
		return;
	}
		
	GameSecond += DeltaSeconds;

	if (GameSecond > 1)
	{
		GameTime += GameSecond;
		GameSecond = 0;
		OnTimerChanged.Broadcast(GameTime);
	}
}

void AMobSurvivorGameMode::ChangeGameCoinsBy(const int Quantity)
{
	GameCoins += Quantity;
	OnCoinsChanged.Broadcast(GameCoins);
}

void AMobSurvivorGameMode::ChangeGamePointsBy(const int Quantity)
{
	GamePoints += Quantity;
	OnPointsChanged.Broadcast(GamePoints);
}