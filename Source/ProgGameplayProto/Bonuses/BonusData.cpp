// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusData.h"

#include "ProgGameplayProto/System/GameUtils.h"
#include "ProgGameplayProto/Characters/ProgGameplayProtoCharacter.h"
#include "ProgGameplayProto/Effects/ProjectileEffect.h"
#include "ProgGameplayProto/Weapons/WeaponComponent.h"

void UBonusData::ApplyOnMainCharacter()
{
	AProgGameplayProtoCharacter* mainCharacter = UGameUtils::GetMainCharacter();
	if (!IsValid(mainCharacter)) return;

	UWeaponComponent* weapon = mainCharacter->GetWeapon();
	if (!IsValid(weapon)) return;

	Apply(mainCharacter, weapon);
}

void UBonusData::Apply(AProgGameplayProtoCharacter* Character, UWeaponComponent* Weapon)
{
	ApplyEffects(Character, Weapon);

	Character->UpdateCharacteristics(CharacterBonuses);
	Weapon->UpdateCharacteristics(WeaponBonuses, ProjectileBonuses);
}

void UBonusData::ApplyEffects(AProgGameplayProtoCharacter* Character, UWeaponComponent* Weapon)
{
	for (int32 i = 0; i < Effects.Num(); i++)
	{
		UProjectileEffect* effect = NewObject<UProjectileEffect>(this, Effects[i]);

		Weapon->AddEffect(effect);
	}
}

int UBonusData::GetRarityValue()
{
	switch (Rarity)
	{
	case Common:
		return 30;
	case Uncommon:
		return 15;
	case Rare:
		return 8;
	case Epic:
		return 3;
	case Legendary:
		return 1;
	default:
		return 0;
	}
}
