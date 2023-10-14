// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusManager.h"

#include "GameLevelData.h"
#include "ProgGameplayProtoGameMode.h"
#include "Bonuses/BonusData.h"
#include "Engine/AssetManager.h"
#include "Engine/ObjectLibrary.h"
#include "Kismet/GameplayStatics.h"

void ABonusManager::BeginPlay()
{
	Super::BeginPlay();

	LoadBonuses();
}

void ABonusManager::LoadBonuses()
{
	AProgGameplayProtoGameMode* gameMode = Cast<AProgGameplayProtoGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	UGameLevelData* gameLevelData = gameMode->GameLevelData;

	if (!IsValid(gameLevelData)) return;

	AllBonuses = gameLevelData->Bonuses;
	AvailableBonuses = AllBonuses;
}

UBonusData* ABonusManager::GetRandomBonus()
{
	if (AvailableBonuses.Num() < 1)
	{
		AvailableBonuses = AllBonuses;
	}

	UBonusData* output = AvailableBonuses[FMath::RandRange(0, AvailableBonuses.Num() - 1)];
	AvailableBonuses.Remove(output);

	return output;
}