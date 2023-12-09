// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinDrop.h"

#include "ProgGameplayProto/System/GameUtils.h"

void ACoinDrop::Collect()
{
	Super::Collect();

	UMobSurvivorSaveGame* GameSave = UGameUtils::GetSaveGame(GetWorld());

	if (IsValid(GameSave))
	{
		GameSave->ParametersToSave.TotalCoins += CoinAmount;
	}

	Destroy();
}
