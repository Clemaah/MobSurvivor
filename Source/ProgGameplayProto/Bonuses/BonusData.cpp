// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusData.h"

#include "ProgGameplayProto/GameUtils.h"
#include "ProgGameplayProto/ProgGameplayProtoCharacter.h"
#include "ProgGameplayProto/Effects/ProjectileEffect.h"
#include "ProgGameplayProto/Weapons/WeaponComponent.h"
#include "ProgGameplayProto/Personas/PersonaComponent.h"

void UBonusData::ApplyOnMainCharacter()
{
	AProgGameplayProtoCharacter* mainCharacter = UGameUtils::GetMainCharacter();
	if (!IsValid(mainCharacter)) return;

	UWeaponComponent* weapon = mainCharacter->GetWeapon();
	if (!IsValid(weapon)) return;

	UPersonaComponent* Persona = mainCharacter->GetPersona();
	if (!IsValid(Persona)) return;

	Apply(mainCharacter, weapon, Persona);
}

void UBonusData::Apply(AProgGameplayProtoCharacter* Character, UWeaponComponent* Weapon, UPersonaComponent* Persona)
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

	Persona->BonusMaxHealth += BonusMaxHealth;
	Persona->BonusRegenerationRate += BonusRegenerationRate;
	Persona->BonusDropChance += BonusDropChance;
	Persona->BonusDropCollectorRadius += BonusDropCollectorRadius;
	Persona->BonusCoinMultiplier += BonusCoinMultiplier;
	Persona->BonusExperienceMultiplier += BonusExperienceMultiplier;
	Persona->BonusNumberOfUpgrades += BonusNumberOfUpgrades;

	Persona->UpdatePersona();
}

void UBonusData::ApplyEffects(AProgGameplayProtoCharacter* Character, UWeaponComponent* Weapon)
{
	for (int32 i = 0; i < Effects.Num(); i++)
	{
		UProjectileEffect* effect = NewObject<UProjectileEffect>(this, Effects[i]);

		Weapon->AddEffect(effect);
	}
}