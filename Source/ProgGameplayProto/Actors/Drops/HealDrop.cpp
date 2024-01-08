// Fill out your copyright notice in the Description page of Project Settings.


#include "HealDrop.h"

#include "ProgGameplayProto/System/GameUtils.h"
#include "ProgGameplayProto/Actors/MobSurvivorCharacter.h"
#include "ProgGameplayProto/ActorComponents/HealthComponent.h"

class AMobSurvivorCharacter;

void AHealDrop::Collect()
{
	Super::Collect();

	AMobSurvivorCharacter* mainCharacter = UGameUtils::GetMainCharacter();

	if (IsValid(mainCharacter))
	{
		mainCharacter->GetHealth()->AddHealth(HealAmount);
	}

	Destroy();
}
