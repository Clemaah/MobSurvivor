// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponData.h"



UWeaponData::UWeaponData()
{
	Levels.Init(FWeaponCharacteristics(), 5);
	LevelsPrice.Init(0, 5);
}

TMap<FString, float> UWeaponData::GetMap(const int Level)
{
	const FWeaponCharacteristics Characteristics = GetLevelCharacteristics(Level);
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

FWeaponCharacteristics UWeaponData::GetLevelCharacteristics(const int Level)
{
	FWeaponCharacteristics ReturnStruct;

	if (Level < 0 || Level >= Levels.Num()) return ReturnStruct;

	int i = 0;

	while (i <= Level)
	{
		ReturnStruct += Levels[i];
		i++;
	}

	return ReturnStruct;
}