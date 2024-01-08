// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterData.h"


UCharacterData::UCharacterData()
{
	Levels.Init(FCharacterLevel(), 5);
}

TArray<FDisplayableCharacteristic> UCharacterData::GetDisplayableCharacteristics_Implementation(const int Level)
{
	TArray<FDisplayableCharacteristic> ReturnArray;
	if (Level >= Levels.Num() || Level < 0)
		return ReturnArray;

	const FPersonaCharacteristics currentPersonaCharacteristics = GetCurrentPersonaCharacteristics(Level);
	const FPersonaCharacteristics nextLevelPersonaCharacteristics = (Level + 1 >= Levels.Num()) ? FPersonaCharacteristics() : Levels[Level + 1].PersonaCharacteristics;

	const FCharacterCharacteristics currentCharacterCharacteristics = GetCurrentCharacterCharacteristics(Level);
	const FCharacterCharacteristics nextLevelCharacterCharacteristics = (Level + 1 >= Levels.Num()) ? FCharacterCharacteristics() : Levels[Level + 1].CharacterCharacteristics;

	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Vie Max"), currentPersonaCharacteristics.MaxHealth, nextLevelPersonaCharacteristics.MaxHealth));
	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("R\u00E9g\u00E9n\u00E9ration"), currentPersonaCharacteristics.RegenerationRate, nextLevelPersonaCharacteristics.RegenerationRate));
	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Vitesse"), currentPersonaCharacteristics.Speed, nextLevelPersonaCharacteristics.Speed));
	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Zone de collecte"), currentCharacterCharacteristics.DropCollectorRadius, nextLevelCharacterCharacteristics.DropCollectorRadius));
	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Nombre de bonus par niveau"), currentCharacterCharacteristics.UpgradesNumber, nextLevelCharacterCharacteristics.UpgradesNumber));
	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Mult. exp\u00E9rience"), currentCharacterCharacteristics.ExperienceMultiplier, nextLevelCharacterCharacteristics.ExperienceMultiplier));
	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Mult. pi\u00E8ces"), currentCharacterCharacteristics.CoinMultiplier, nextLevelCharacterCharacteristics.CoinMultiplier));
	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Mult. chance d'apparition de pi\u00E8ces"), currentCharacterCharacteristics.CoinDropChanceMultiplier, nextLevelCharacterCharacteristics.CoinDropChanceMultiplier));
	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Mult. chance d'apparition de bonus"), currentCharacterCharacteristics.UpgradeDropChanceMultiplier, nextLevelCharacterCharacteristics.UpgradeDropChanceMultiplier));
	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Mult. chance de double shot"), currentPersonaCharacteristics.DoubleShotChanceMultiplier, nextLevelPersonaCharacteristics.DoubleShotChanceMultiplier));
	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Mult. cadence de tir"), currentPersonaCharacteristics.FireRateMultiplier, nextLevelPersonaCharacteristics.FireRateMultiplier));
	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Mult. pr\u00E9cision"), currentPersonaCharacteristics.PrecisionMultiplier, nextLevelPersonaCharacteristics.PrecisionMultiplier));
	ReturnArray.Add(FDisplayableCharacteristic(FText::INVTEXT("Mult. spread"), currentPersonaCharacteristics.SpreadMultiplier, nextLevelPersonaCharacteristics.SpreadMultiplier));

	return ReturnArray;
}

int UCharacterData::GetLevelPrice_Implementation(const int Level)
{
	if (Level < 0 || Level >= Levels.Num()) return 0;

	return Levels[Level].Price;
}

FPersonaCharacteristics UCharacterData::GetCurrentPersonaCharacteristics(const int Level)
{
	FPersonaCharacteristics ReturnStruct;

	if (Level < 0 || Level >= Levels.Num()) return ReturnStruct;

	int i = 0;

	while (i <= Level)
	{
		ReturnStruct += Levels[i].PersonaCharacteristics;
		i++;
	}

	return ReturnStruct;
}

FCharacterCharacteristics UCharacterData::GetCurrentCharacterCharacteristics(const int Level)
{
	FCharacterCharacteristics ReturnStruct;

	if (Level < 0 || Level >= Levels.Num()) return ReturnStruct;

	int i = 0;

	while (i <= Level)
	{
		ReturnStruct += Levels[i].CharacterCharacteristics;
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