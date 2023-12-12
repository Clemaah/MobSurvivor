// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusManager.h"

#include "ProgGameplayProto/LevelData.h"
#include "ProgGameplayProto/System/MobSurvivorGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "ProgGameplayProto/Bonuses/BonusData.h"

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
	UBonusData* bonus = AvailableBonuses[GetWeightedIndex()];

	return bonus;
}

void ABonusManager::AddToHeldBonuses(UBonusData* Bonus)
{
	int* bonusCurrentLevelPointer = HeldBonus.Find(Bonus);

	if (!bonusCurrentLevelPointer)
		HeldBonus.Add(Bonus, 1);

	else
		HeldBonus[Bonus] += 1;

	if (HeldBonus[Bonus] >= Bonus->MaxStack)
		AvailableBonuses.Remove(Bonus);
}

int ABonusManager::GetWeightedIndex()
{
	float totalWeight = 0;

	for (int i = 0; i < AvailableBonuses.Num(); i++)
	{
		totalWeight += AvailableBonuses[i]->RarityWeight;
	}

	const float randomSelectedWeight = FMath::FRandRange(0, totalWeight);
	float weightsSum = 0;

	for (int i = 0; i < AvailableBonuses.Num(); i++)
	{
		weightsSum += AvailableBonuses[i]->RarityWeight;

		if (randomSelectedWeight <= weightsSum)
			return i;
	}

	return 0;
}