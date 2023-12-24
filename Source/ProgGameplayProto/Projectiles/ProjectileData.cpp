// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileData.h"
#include "ProjectileCharacteristics.h"
#include "ProgGameplayProto/DisplayablePlayerElementInterface.h"


UProjectileData::UProjectileData()
{
	Levels.Init(FProjectileLevel(), 5);
}

TArray<FDisplayableCharacteristic> UProjectileData::GetDisplayableCharacteristics_Implementation(const int Level)
{
	TArray<FDisplayableCharacteristic> ReturnArray;
	if (Level >= Levels.Num() || Level < 0)
		return ReturnArray;

	const FProjectileCharacteristics currentCharacteristics = GetCurrentCharacteristics(Level);
	const FProjectileCharacteristics nextLevelCharacteristics = (Level + 1 >= Levels.Num()) ? FProjectileCharacteristics() : Levels[Level + 1].Characteristics;

	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("D\u00E9g\u00E2ts"), currentCharacteristics.Damages, nextLevelCharacteristics.Damages));
	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Port\u00E9e"), currentCharacteristics.Range, nextLevelCharacteristics.Range));
	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Taille"), currentCharacteristics.Size, nextLevelCharacteristics.Size));
	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Vitesse"), currentCharacteristics.Speed, nextLevelCharacteristics.Speed));
	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Chance de critique"), currentCharacteristics.CriticalHitChance, nextLevelCharacteristics.CriticalHitChance));
	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Mult. critique"), currentCharacteristics.CriticalHitMultiplier, nextLevelCharacteristics.CriticalHitMultiplier));

	return ReturnArray;
}

int UProjectileData::GetLevelPrice_Implementation(const int Level)
{
	if (Level < 0 || Level >= Levels.Num()) return 0;

	return Levels[Level].Price;
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

FText UProjectileData::GetName_Implementation()
{
	return FText::FromString(Name);
}

FText UProjectileData::GetDescription_Implementation()
{
	return Description;
}