// Fill out your copyright notice in the Description page of Project Settings.


#include "HealDrop.h"

#include "ProgGameplayProto/HealthComponent.h"
#include "ProgGameplayProto/System/GameUtils.h"
#include "ProgGameplayProto/Characters/ProgGameplayProtoCharacter.h"

void AHealDrop::Collect()
{
	Super::Collect();

	AProgGameplayProtoCharacter* mainCharacter = UGameUtils::GetMainCharacter();

	if (IsValid(mainCharacter))
	{
		mainCharacter->GetHealth()->AddHealth(HealAmount);
	}

	Destroy();
}
