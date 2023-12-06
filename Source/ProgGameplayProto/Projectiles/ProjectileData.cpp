// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileData.h"



UProjectileData::UProjectileData()
{
	Levels.Init(FProjectileLevel(), 5);
}

TMap<FString, float> UProjectileData::GetMap(const int Level)
{
	const FProjectileCharacteristics Characteristics = GetCurrentCharacteristics(Level);
	TMap<FString, float> ReturnMap;

	ReturnMap.Add(TEXT("Damages"), Characteristics.Damages);
	ReturnMap.Add(TEXT("Range"), Characteristics.Range);
	ReturnMap.Add(TEXT("Size"), Characteristics.Size);
	ReturnMap.Add(TEXT("Speed"), Characteristics.Speed);
	ReturnMap.Add(TEXT("CriticalHitChance"), Characteristics.CriticalHitChance);
	ReturnMap.Add(TEXT("CriticalHitMultiplier"), Characteristics.CriticalHitMultiplier);

	return ReturnMap;
}

FProjectileCharacteristics UProjectileData::GetCurrentCharacteristics(const int Level)
{
	FProjectileCharacteristics ReturnStruct;

	if (Level < 0 || Level >= Levels.Num()) return ReturnStruct;

	int i = 0;

	while (i <= Level)
	{
		ReturnStruct += Levels[i].Characteristics;
		i++;
	}

	return ReturnStruct;
}