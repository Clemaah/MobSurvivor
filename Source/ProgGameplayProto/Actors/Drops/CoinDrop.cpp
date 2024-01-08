// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinDrop.h"

#include "ProgGameplayProto/System/GameUtils.h"
#include "ProgGameplayProto/System/MobSurvivorGameMode.h"

void ACoinDrop::Collect()
{
	Super::Collect();

	AMobSurvivorGameMode* GameMode = UGameUtils::GetGameMode(GetWorld());

	if (IsValid(GameMode))
		GameMode->ChangeGameCoinsBy(CoinAmount);

	Destroy();
}
