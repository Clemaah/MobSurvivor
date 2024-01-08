// Fill out your copyright notice in the Description page of Project Settings.


#include "ExperienceDrop.h"

#include "ProgGameplayProto/System/GameUtils.h"
#include "ProgGameplayProto/Actors/MobSurvivorCharacter.h"
#include "ProgGameplayProto/ActorComponents/ExperienceComponent.h"


void AExperienceDrop::Collect()
{
	Super::Collect();

	AMobSurvivorCharacter* mainCharacter = UGameUtils::GetMainCharacter();

	if (IsValid(mainCharacter))
	{
		mainCharacter->GetExperience()->AddExperience(ExperienceAmount);
	}

	Destroy();
}
