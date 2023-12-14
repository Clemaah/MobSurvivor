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
		
	GameTime += DeltaSeconds;
}

float AMobSurvivorGameMode::GetCurrentProgressionPercentage() const
{
	float output = GameTime / GameLevelData->Duration;

	output = FMath::Clamp(output, 0, 1);

	return output;
}
