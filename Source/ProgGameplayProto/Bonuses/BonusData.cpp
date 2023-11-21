// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusData.h"

#include "ProgGameplayProto/GameUtils.h"
#include "ProgGameplayProto/ProgGameplayProtoCharacter.h"
#include "ProgGameplayProto/Effects/ProjectileEffect.h"
#include "ProgGameplayProto/Weapons/WeaponComponent.h"
#include "ProgGameplayProto/Abilities/AbilitiesComponent.h"

void UBonusData::ApplyOnMainCharacter()
{
	AProgGameplayProtoCharacter* mainCharacter = UGameUtils::GetMainCharacter();
	if (!IsValid(mainCharacter)) return;

	UWeaponComponent* weapon = mainCharacter->GetWeapon();
	if (!IsValid(weapon)) return;

	UAbilitiesComponent* abilities = mainCharacter->GetAbilities();
	if (!IsValid(abilities)) return;

	Apply(mainCharacter, weapon, abilities);
}

void UBonusData::Apply(AProgGameplayProtoCharacter* Character, UWeaponComponent* Weapon, UAbilitiesComponent* Abilities)
{
	ApplyEffects(Character, Weapon);

	Weapon->BonusFireRate += BonusFireRate;
	Weapon->BonusFireRateMultiplier += BonusFireRateMultiplier;
	Weapon->BonusNumberOfShots += BonusNumberOfShots;
	Weapon->BonusNumberOfShotsMultiplier += BonusNumberOfShotsMultiplier;
	Weapon->BonusPrecision += BonusPrecision;
	Weapon->BonusPrecisionMultiplier += BonusPrecisionMultiplier;
	Weapon->BonusSpread += BonusSpread;
	Weapon->BonusSpreadMultiplier += BonusSpreadMultiplier;
	Weapon->BonusDamages += BonusDamages;
	Weapon->BonusDamagesMultiplier += BonusDamagesMultiplier;
	Weapon->BonusProjectileSize += BonusProjectileSize;
	Weapon->BonusProjectileSizeMultiplier += BonusProjectileSizeMultiplier;
	Weapon->BonusRange += BonusRange;
	Weapon->BonusRangeMultiplier += BonusRangeMultiplier;
	Weapon->BonusProjectileSpeed += BonusProjectileSpeed;
	Weapon->BonusProjectileSpeedMultiplier += BonusProjectileSpeedMultiplier;
	Weapon->BonusCriticalHitChance += BonusCriticalHitChance;
	Weapon->BonusCriticalHitChanceMultiplier += BonusCriticalHitChanceMultiplier;
	Weapon->BonusCriticalHitDamageMultiplier += BonusCriticalHitDamageMultiplier;

	Abilities->BonusMaxHealth += BonusMaxHealth;
	Abilities->BonusRegenerationRate += BonusRegenerationRate;
	Abilities->BonusDropChance += BonusDropChance;
	Abilities->BonusDropMultiplier += BonusDropMultiplier;
	Abilities->BonusDropCollectorRadius += BonusDropCollectorRadius;
	Abilities->BonusNumberOfUpgrades += BonusNumberOfUpgrades;

	Abilities->UpdateAbilities();
}

void UBonusData::ApplyEffects(AProgGameplayProtoCharacter* Character, UWeaponComponent* Weapon)
{
	for (int32 i = 0; i < Effects.Num(); i++)
	{
		UProjectileEffect* effect = NewObject<UProjectileEffect>(this, Effects[i]);

		Weapon->AddEffect(effect);
	}
}