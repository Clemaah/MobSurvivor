// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusData.h"

#include "ProgGameplayProto/ActorComponents/WeaponComponent.h"
#include "ProgGameplayProto/System/GameUtils.h"

void UBonusData::ApplyOnMainCharacter()
{
	AMobSurvivorCharacter* mainCharacter = UGameUtils::GetMainCharacter();
	if (!IsValid(mainCharacter)) return;

	UWeaponComponent* weapon = mainCharacter->GetWeapon();
	if (!IsValid(weapon)) return;

	Apply(mainCharacter, weapon);
}

void UBonusData::Apply(AMobSurvivorCharacter* Character, UWeaponComponent* Weapon)
{
	Character->UpdateCharacteristics(PersonaBonuses, CharacterBonuses);
	Weapon->UpdateCharacteristics(WeaponBonuses, ProjectileBonuses);

	for (TSubclassOf<UProjectileEffect> effect : Effects)
		Weapon->AddEffect(effect);
}

int UBonusData::GetRarityValue()
{
	switch (Rarity)
	{
	case Common:
		return 15;
	case Uncommon:
		return 10;
	case Rare:
		return 5;
	case Epic:
		return 3;
	case Legendary:
		return 1;
	default:
		return 0;
	}
}
