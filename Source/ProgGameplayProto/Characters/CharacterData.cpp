// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterData.h"
#include "CharacterCharacteristics.h"
#include "ProgGameplayProto/DisplayablePlayerElementInterface.h"


UCharacterData::UCharacterData()
{
	Levels.Init(FCharacterLevel(), 5);
}

TArray<FDisplayableCharacteristic> UCharacterData::GetDisplayableCharacteristics_Implementation(const int Level)
{
	TArray<FDisplayableCharacteristic> ReturnArray;
	if (Level >= Levels.Num() || Level < 0)
		return ReturnArray;

	const FCharacterCharacteristics currentCharacteristics = GetCurrentCharacteristics(Level);
	const FCharacterCharacteristics nextLevelCharacteristics = (Level + 1 >= Levels.Num()) ? FCharacterCharacteristics() : Levels[Level + 1].Characteristics;

	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Vie Max"), currentCharacteristics.MaxHealth, nextLevelCharacteristics.MaxHealth));
	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("R\u00E9g\u00E9n\u00E9ration"), currentCharacteristics.RegenerationRate, nextLevelCharacteristics.RegenerationRate));
	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Vitesse"), currentCharacteristics.Speed, nextLevelCharacteristics.Speed));
	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Zone de collecte"), currentCharacteristics.DropCollectorRadius, nextLevelCharacteristics.DropCollectorRadius));
	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Nombre de bonus par niveau"), currentCharacteristics.UpgradesNumber, nextLevelCharacteristics.UpgradesNumber));
	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Mult. exp\u00E9rience"), currentCharacteristics.ExperienceMultiplier, nextLevelCharacteristics.ExperienceMultiplier));
	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Mult. pi\u00E8ces"), currentCharacteristics.CoinMultiplier, nextLevelCharacteristics.CoinMultiplier));
	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Mult. chance d'apparition de pi\u00E8ces"), currentCharacteristics.CoinDropChanceMultiplier, nextLevelCharacteristics.CoinDropChanceMultiplier));
	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Mult. chance d'apparition de bonus"), currentCharacteristics.UpgradeDropChanceMultiplier, nextLevelCharacteristics.UpgradeDropChanceMultiplier));
	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Mult. chance de double shot"), currentCharacteristics.DoubleShotChanceMultiplier, nextLevelCharacteristics.DoubleShotChanceMultiplier));
	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Mult. cadence de tir"), currentCharacteristics.FireRateMultiplier, nextLevelCharacteristics.FireRateMultiplier));
	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Mult. pr\u00E9cision"), currentCharacteristics.PrecisionMultiplier, nextLevelCharacteristics.PrecisionMultiplier));
	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Mult. spread"), currentCharacteristics.SpreadMultiplier, nextLevelCharacteristics.SpreadMultiplier));

	return ReturnArray;
}

int UCharacterData::GetLevelPrice_Implementation(const int Level)
{
	if (Level < 0 || Level >= Levels.Num()) return 0;

	return Levels[Level].Price;
}

FCharacterCharacteristics UCharacterData::GetCurrentCharacteristics(const int Level)
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

FText UCharacterData::GetName_Implementation()
{
	return FText::FromString(Name);
}

FText UCharacterData::GetDescription_Implementation()
{
	return Description;
}