// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponData.h"
#include "WeaponCharacteristics.h"
#include "ProgGameplayProto/DisplayablePlayerElementInterface.h"



UWeaponData::UWeaponData()
{
	Levels.Init(FWeaponLevel(), 5);
}

TArray<FDisplayableCharacteristic> UWeaponData::GetDisplayableCharacteristics_Implementation(const int Level)
{
	TArray<FDisplayableCharacteristic> ReturnArray;
	if (Level >= Levels.Num() || Level < 0)
		return ReturnArray;

	const FWeaponCharacteristics currentCharacteristics = GetCurrentCharacteristics(Level);
	const FWeaponCharacteristics nextLevelCharacteristics = (Level + 1 >= Levels.Num()) ? FWeaponCharacteristics() : Levels[Level + 1].Characteristics;

	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Cadence de tir"), currentCharacteristics.FireRate, nextLevelCharacteristics.FireRate));
	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Pr\u00E9cision"), currentCharacteristics.Precision, nextLevelCharacteristics.Precision));
	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Spread"), currentCharacteristics.Spread, nextLevelCharacteristics.Spread));
	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Double Shot"), currentCharacteristics.DoubleShotChance, nextLevelCharacteristics.DoubleShotChance));
	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Nombre de projectiles"), currentCharacteristics.ShotsNumber, nextLevelCharacteristics.ShotsNumber));
	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Mult. d\u00E9g\u00E2ts"), currentCharacteristics.DamagesMultiplier, nextLevelCharacteristics.DamagesMultiplier));
	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Mult. port\u00E9e des projectiles"), currentCharacteristics.RangeMultiplier, nextLevelCharacteristics.RangeMultiplier));
	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Mult. taille des projectiles"), currentCharacteristics.ProjectileSizeMultiplier, nextLevelCharacteristics.ProjectileSizeMultiplier));
	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Mult. vitesse des projectiles"), currentCharacteristics.ProjectileSpeedMultiplier, nextLevelCharacteristics.ProjectileSpeedMultiplier));
	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Mult. chance critiques"), currentCharacteristics.CriticalHitChanceMultiplier, nextLevelCharacteristics.CriticalHitChanceMultiplier));

	return ReturnArray;
}

int UWeaponData::GetLevelPrice_Implementation(const int Level)
{
	if (Level < 0 || Level >= Levels.Num()) return 0;

	return Levels[Level].Price;
}

FWeaponCharacteristics UWeaponData::GetCurrentCharacteristics(const int Level)
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

FText UWeaponData::GetName_Implementation()
{
	return FText::FromString(Name);
}

FText UWeaponData::GetDescription_Implementation()
{
	return Description;
}