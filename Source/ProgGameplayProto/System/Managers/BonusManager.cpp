// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusManager.h"

#include "ProgGameplayProto/System/MobSurvivorGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "ProgGameplayProto/DataAssets/Bonuses/BonusData.h"

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

	ResetAvailableBonuses();
}

void ABonusManager::ResetAvailableBonuses()
{
	AvailableBonuses = AllBonuses;
}

UBonusData* ABonusManager::GetRandomBonus()
{
	if(AvailableBonuses.Num() == 0)
	{
		return nullptr;
	}

	int bonusIndex = GetWeightedIndex();

	UBonusData* bonus = AvailableBonuses[bonusIndex];
	AvailableBonuses.RemoveAtSwap(bonusIndex);

	return bonus;
}

void ABonusManager::AddToHeldBonuses(UBonusData* Bonus)
{
	HeldBonus.FindOrAdd(Bonus, 0);
	HeldBonus[Bonus] += 1;

	if (HeldBonus[Bonus] >= Bonus->LevelMax)
		AllBonuses.Remove(Bonus);
}

int ABonusManager::GetWeightedIndex()
{                                       
	float totalWeight = 0;

	for (int i = 0; i < AvailableBonuses.Num(); i++)
		totalWeight += AvailableBonuses[i]->GetRarityValue() * (AvailableBonuses[i]->LevelMax - HeldBonus.FindRef(AvailableBonuses[i]));

	const float randomSelectedWeight = FMath::FRandRange(0, totalWeight);
	float weightsSum = 0;

	for (int i = 0; i < AvailableBonuses.Num(); i++)
	{
		weightsSum += AvailableBonuses[i]->GetRarityValue() * (AvailableBonuses[i]->LevelMax - HeldBonus.FindRef(AvailableBonuses[i]));

		if (randomSelectedWeight <= weightsSum)
			return i;
	}

	return 0;
}