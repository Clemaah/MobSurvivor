// Fill out your copyright notice in the Description page of Project Settings.


#include "ExperienceDrop.h"

#include "DropperComponent.h"
#include "ProgGameplayProto/ExperienceComponent.h"
#include "ProgGameplayProto/GameUtils.h"
#include "ProgGameplayProto/ProgGameplayProtoCharacter.h"

void AExperienceDrop::Collect()
{
	Super::Collect();

	AProgGameplayProtoCharacter* mainCharacter = UGameUtils::GetMainCharacter();

	if (IsValid(mainCharacter))
	{
		mainCharacter->GetExperience()->AddExperience(ExperienceAmount);
	}

	Destroy();
}
