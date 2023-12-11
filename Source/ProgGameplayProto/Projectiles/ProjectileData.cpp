// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileData.h"

#include "ProgGameplayProto/Characters/ProgGameplayProtoCharacter.h"
#include "ProgGameplayProto/Weapons/WeaponComponent.h"
#include "ProgGameplayProto/Effects/ProjectileEffect.h"
#include "ProgGameplayProto/Effects/BounceEffect.h"


UProjectileData::UProjectileData()
{
	Levels.Init(FProjectileLevel(), 5);
}

TMap<FString, float> UProjectileData::GetMap(const int Level)
{
	const FProjectileCharacteristics Characteristics = GetLevelCharacteristics(Level);
	TMap<FString, float> ReturnMap;

	ReturnMap.Add(TEXT("Damages"), Characteristics.Damages);
	ReturnMap.Add(TEXT("Range"), Characteristics.Range);
	ReturnMap.Add(TEXT("Size"), Characteristics.Size);
	ReturnMap.Add(TEXT("Speed"), Characteristics.Speed);
	ReturnMap.Add(TEXT("CriticalHitChance"), Characteristics.CriticalHitChance);
	ReturnMap.Add(TEXT("CriticalHitMultiplier"), Characteristics.CriticalHitMultiplier);

	return ReturnMap;
}

FProjectileCharacteristics UProjectileData::GetLevelCharacteristics(const int Level)
{
	FProjectileCharacteristics ReturnStruct;

	if (Level < 0 || Level >= Levels.Num()) return ReturnStruct;

	int i = 0;

	while (i <= Level)
	{
		ReturnStruct += Levels[i].Characteristics;
		i++;
	}

	return ReturnStruct;
}

int UProjectileData::GetLevelPrice(const int Level)
{
	if (Level < 0 || Level >= Levels.Num()) 
		return -1;

	return Levels[Level].Price;
}

void UProjectileData::Apply(AProgGameplayProtoCharacter* Character, UWeaponComponent* Weapon)
{
	ApplyEffects(Character, Weapon);

}

void UProjectileData::ApplyEffects(AProgGameplayProtoCharacter* Character, UWeaponComponent* Weapon)
{
	for (int32 i = 0; i < Effects.Num(); i++)
	{
		UProjectileEffect* effect = NewObject<UProjectileEffect>(this, Effects[i]);

		Weapon->AddEffect(effect);
	}
}