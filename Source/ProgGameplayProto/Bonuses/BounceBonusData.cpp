// Fill out your copyright notice in the Description page of Project Settings.


#include "BounceBonusData.h"
#include "ProgGameplayProto/Effects/BounceEffect.h"
#include "ProgGameplayProto/Weapons/WeaponComponent.h"

void UBounceBonusData::Apply(AProgGameplayProtoCharacter* Character, UWeaponComponent* Weapon, UAbilityComponent* Ability)
{
	Super::Apply(Character, Weapon, Ability);

	UBounceEffect* effect = NewObject<UBounceEffect>(this, BounceEffect);
	effect->NumberOfAdditionalBounces = NumberOfBounces;

	Weapon->AddEffect(effect);
}