// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterData.h"
#include "CharacterCharacteristics.h"


UCharacterData::UCharacterData()
{
	Levels.Init(FCharacterLevel(), 5);
}

TMap<FString, float> UCharacterData::GetCumulativeLevelsMap(const int Level)
{
	if (Level >= Levels.Num() || Level < 0)
	{
		TMap<FString, float> EmptyMap;
		return EmptyMap;
	}

	const FCharacterCharacteristics characteristics = GetCumulativeLevelsCharacteristics(Level);

	return GetMap(characteristics, Level);
}

TMap<FString, float> UCharacterData::GetLevelMap(const int Level)
{
	if (Level >= Levels.Num() || Level < 0)
	{
		TMap<FString, float> EmptyMap;
		return EmptyMap;
	}

	const FCharacterCharacteristics characteristics = Levels[Level].Characteristics;

	return GetMap(characteristics, Level);
}

TMap<FString, float> UCharacterData::GetMap(const FCharacterCharacteristics& Characteristics, const int Level)
{
	TMap<FString, float> ReturnMap;

	ReturnMap.Add(TEXT("MaxHealth"), Characteristics.MaxHealth);
	ReturnMap.Add(TEXT("RegenerationRate"), Characteristics.RegenerationRate);
	ReturnMap.Add(TEXT("Speed"), Characteristics.Speed);
	ReturnMap.Add(TEXT("DropCollectorRadius"), Characteristics.DropCollectorRadius);
	ReturnMap.Add(TEXT("ExperienceMultiplier"), Characteristics.ExperienceMultiplier);
	ReturnMap.Add(TEXT("CoinMultiplier"), Characteristics.CoinMultiplier);
	ReturnMap.Add(TEXT("CoinDropChanceMultiplier"), Characteristics.CoinDropChanceMultiplier);
	ReturnMap.Add(TEXT("UpgradeDropChanceMultiplier"), Characteristics.UpgradeDropChanceMultiplier);
	ReturnMap.Add(TEXT("UpgradesNumber"), Characteristics.UpgradesNumber);
	ReturnMap.Add(TEXT("DoubleShotChanceMultiplier"), Characteristics.DoubleShotChanceMultiplier);
	ReturnMap.Add(TEXT("FireRateMultiplier"), Characteristics.FireRateMultiplier);
	ReturnMap.Add(TEXT("PrecisionMultiplier"), Characteristics.PrecisionMultiplier);
	ReturnMap.Add(TEXT("SpreadMultiplier"), Characteristics.SpreadMultiplier);

	return ReturnMap;
}

FCharacterCharacteristics UCharacterData::GetCumulativeLevelsCharacteristics(const int Level)
{
	FCharacterCharacteristics ReturnStruct;

	if (Level < 0 || Level >= Levels.Num()) return ReturnStruct;

	int i = 0;

	while (i <= Level)
	{
		ReturnStruct += Levels[i].Characteristics;
		i++;
	}

	return ReturnStruct;
}

int UCharacterData::GetLevelPrice(const int Level)
{
	if (Level < 0 || Level >= Levels.Num()) return 0;

	return Levels[Level].Price;
}