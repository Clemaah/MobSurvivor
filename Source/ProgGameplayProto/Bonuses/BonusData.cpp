// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusData.h"

#include "ProgGameplayProto/GameUtils.h"
#include "ProgGameplayProto/ProgGameplayProtoCharacter.h"
#include "ProgGameplayProto/Effects/ProjectileEffect.h"
#include "ProgGameplayProto/Weapons/WeaponComponent.h"
#include "ProgGameplayProto/Abilities/AbilityComponent.h"

void UBonusData::ApplyOnMainCharacter()
{
	AProgGameplayProtoCharacter* mainCharacter = UGameUtils::GetMainCharacter();
	if (!IsValid(mainCharacter)) return;

	UWeaponComponent* weapon = mainCharacter->GetWeapon();
	if (!IsValid(weapon)) return;

	UAbilityComponent* ability = mainCharacter->GetAbility();
	if (!IsValid(ability)) return;

	Apply(mainCharacter, weapon, ability);
}

void UBonusData::Apply(AProgGameplayProtoCharacter* Character, UWeaponComponent* Weapon, UAbilityComponent* Ability)
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

	Ability->BonusMaxHealth += BonusMaxHealth;
	Ability->BonusRegenerationRate += BonusRegenerationRate;
	Ability->BonusDropChance += BonusDropChance;
	Ability->BonusDropMultiplier += BonusDropMultiplier;
	Ability->BonusDropCollectorRadius += BonusDropCollectorRadius;
	Ability->BonusNumberOfUpgrades += BonusNumberOfUpgrades;

	Ability->UpdateAbility();
}

void UBonusData::ApplyEffects(AProgGameplayProtoCharacter* Character, UWeaponComponent* Weapon)
{
	for (int32 i = 0; i < Effects.Num(); i++)
	{
		UProjectileEffect* effect = NewObject<UProjectileEffect>(this, Effects[i]);

		Weapon->AddEffect(effect);
	}
}