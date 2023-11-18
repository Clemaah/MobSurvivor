// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProgGameplayProtoGameMode.h"

#include "EnemySpawnerManager.h"
#include "BonusManager.h"
#include "UpgradesManager.h"
#include "ProgGameplayProtoCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProgGameplayProtoGameMode::AProgGameplayProtoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AProgGameplayProtoGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	EnemySpawnerManager = GetWorld()->SpawnActor<AEnemySpawnerManager>();
	BonusManager = GetWorld()->SpawnActor<ABonusManager>();
	UpgradesManager = GetWorld()->SpawnActor<AUpgradesManager>();
}