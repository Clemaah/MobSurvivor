// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyData.h"


UEnemyData::UEnemyData()
{
	Levels.Init(FEnemyLevel(), 1);
}

FPersonaCharacteristics UEnemyData::GetCurrentPersonaCharacteristics(const int Level)
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

FEnemyCharacteristics UEnemyData::GetCurrentEnemyCharacteristics(const int Level)
{
	FEnemyCharacteristics ReturnStruct;

	if (Level < 0 || Level >= Levels.Num()) return ReturnStruct;

	int i = 0;

	while (i <= Level)
	{
		ReturnStruct += Levels[i].EnemyCharacteristics;
		i++;
	}

	return ReturnStruct;
}