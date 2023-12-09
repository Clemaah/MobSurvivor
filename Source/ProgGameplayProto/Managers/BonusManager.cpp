// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusManager.h"

#include "ProgGameplayProto/LevelData.h"
#include "ProgGameplayProto/System/MobSurvivorGameMode.h"
#include "Kismet/GameplayStatics.h"

void ABonusManager::BeginPlay()
{
	Super::BeginPlay();

	LoadBonuses();
}

void ABonusManager::LoadBonuses()
{
	AMobSurvivorGameMode* gameMode = Cast<AMobSurvivorGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	ULevelData* gameLevelData = gameMode->GameLevelData;

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