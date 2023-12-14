// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageArea.h"

#include "ProgGameplayProto/Drops/CoinDrop.h"
#include "ProgGameplayProto/System/GameUtils.h"

void ADamageArea::Collect()
{
	Super::Collect();

	UMobSurvivorSaveGame* GameSave = UGameUtils::GetSaveGame(GetWorld());

	if (IsValid(GameSave))
	{
		GameSave->TotalCoins += CoinAmount;
	}
	
	Destroy();
}
