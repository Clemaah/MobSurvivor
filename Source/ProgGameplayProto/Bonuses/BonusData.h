// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ProgGameplayProto/Characters/CharacterCharacteristics.h"
#include "ProgGameplayProto/Projectiles/ProjectileCharacteristics.h"
#include "ProgGameplayProto/Weapons/WeaponCharacteristics.h"
#include "BonusData.generated.h"

class UProjectileEffect;
class AProgGameplayProtoCharacter;
class UWeaponComponent;
/**
 *
 */

UCLASS(BlueprintType)
class PROGGAMEPLAYPROTO_API UBonusData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meta", meta = (MultiLine = true))
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meta", meta = (MultiLine = true))
	int MaxStack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Effects")
	TArray<TSubclassOf<UProjectileEffect>> Effects;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (ShowOnlyInnerProperties))
	FCharacterCharacteristics CharacterBonuses;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (ShowOnlyInnerProperties))
	FWeaponCharacteristics WeaponBonuses;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (ShowOnlyInnerProperties))
	FProjectileCharacteristics ProjectileBonuses;

public:
	UFUNCTION(BlueprintCallable)
	virtual void ApplyOnMainCharacter();

	virtual void Apply(AProgGameplayProtoCharacter* Character, UWeaponComponent* Weapon);

	virtual void ApplyEffects(AProgGameplayProtoCharacter* Character, UWeaponComponent* Weapon);
};
