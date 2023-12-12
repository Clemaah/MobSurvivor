// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponData.h"



UWeaponData::UWeaponData()
{
	Levels.Init(FWeaponLevel(), 5);
}

TMap<FString, float> UWeaponData::GetCumulativeLevelsMap(const int Level)
{
	if (Level >= Levels.Num() || Level < 0)
	{
		TMap<FString, float> EmptyMap;
		return EmptyMap;
	}

	const FWeaponCharacteristics characteristics = GetCumulativeLevelsCharacteristics(Level);

	return GetMap(characteristics, Level);
}

TMap<FString, float> UWeaponData::GetLevelMap(const int Level)
{
	if (Level >= Levels.Num() || Level < 0)
	{
		TMap<FString, float> EmptyMap;
		return EmptyMap;
	}

	const FWeaponCharacteristics characteristics = Levels[Level].Characteristics;

	return GetMap(characteristics, Level);
}

TMap<FString, float> UWeaponData::GetMap(const FWeaponCharacteristics& Characteristics, const int Level)
{
	TMap<FString, float> ReturnMap;

	ReturnMap.Add(TEXT("FireRate"), Characteristics.FireRate);
	ReturnMap.Add(TEXT("Precision"), Characteristics.Precision);
	ReturnMap.Add(TEXT("Spread"), Characteristics.Spread);
	ReturnMap.Add(TEXT("DoubleShotsChance"), Characteristics.DoubleShotChance);
	ReturnMap.Add(TEXT("ShotsNumber"), Characteristics.ShotsNumber);
	ReturnMap.Add(TEXT("DamagesMultiplier"), Characteristics.DamagesMultiplier);
	ReturnMap.Add(TEXT("RangeMultiplier"), Characteristics.RangeMultiplier);
	ReturnMap.Add(TEXT("ProjectileSizeMultiplier"), Characteristics.ProjectileSizeMultiplier);
	ReturnMap.Add(TEXT("ProjectileSpeedMultiplier"), Characteristics.ProjectileSpeedMultiplier);
	ReturnMap.Add(TEXT("CriticalHitChanceMultiplier"), Characteristics.CriticalHitChanceMultiplier);

	return ReturnMap;
}

FWeaponCharacteristics UWeaponData::GetCumulativeLevelsCharacteristics(const int Level)
{
	FWeaponCharacteristics ReturnStruct;

	if (Level < 0 || Level >= Levels.Num()) return ReturnStruct;

	int i = 0;

	while (i <= Level)
	{
		ReturnStruct += Levels[i].Characteristics;
		i++;
	}

	return ReturnStruct;
}

int UWeaponData::GetLevelPrice(const int Level)
{
	if (Level < 0 || Level >= Levels.Num()) return 0;

	return Levels[Level].Price;
}