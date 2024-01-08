// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ProgGameplayProto/DataAssets/PersonaCharacteristics.h"
#include "ProgGameplayProto/DataAssets/Projectiles/ProjectileCharacteristics.h"
#include "ProgGameplayProto/DataAssets/Weapons/WeaponCharacteristics.h"
#include "ProgGameplayProto/Actors/MobSurvivorCharacter.h"
#include "BonusData.generated.h"
/**
 *
 */

class UProjectileEffect;

UENUM(BlueprintType)
enum ERarity { Legendary, Epic, Rare, Uncommon, Common };


UCLASS(BlueprintType)
class PROGGAMEPLAYPROTO_API UBonusData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meta", meta = (MultiLine = true))
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meta", meta = (ClampMin = 1, ClampMax = 10))
	int LevelMax = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meta")
	TEnumAsByte<ERarity> Rarity = Common;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Effects")
	TArray<TSubclassOf<UProjectileEffect>> Effects;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (ShowOnlyInnerProperties))
	FCharacterCharacteristics CharacterBonuses;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (ShowOnlyInnerProperties))
	FPersonaCharacteristics PersonaBonuses;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (ShowOnlyInnerProperties))
	FWeaponCharacteristics WeaponBonuses;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (ShowOnlyInnerProperties))
	FProjectileCharacteristics ProjectileBonuses;

public:
	UFUNCTION(BlueprintCallable)
	virtual void ApplyOnMainCharacter();

	virtual void Apply(AMobSurvivorCharacter* Character, UWeaponComponent* Weapon);

	virtual int GetRarityValue();
};
