// Fill out your copyright notice in the Description page of Project Settings.


#include "GameUtils.h"

#include "Characters/ProgGameplayProtoCharacter.h"

AProgGameplayProtoCharacter* UGameUtils::GetMainCharacter()
{
	return AProgGameplayProtoCharacter::Instance;
}
