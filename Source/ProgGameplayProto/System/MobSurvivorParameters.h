// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProgGameplayProto/Characters/CharacterData.h"
#include "ProgGameplayProto/Projectiles/ProjectileData.h"
#include "ProgGameplayProto/Weapons/WeaponData.h"
#include "MobSurvivorParameters.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct PROGGAMEPLAYPROTO_API FMobSurvivorParameters
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TotalCoins;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PlayerToken;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCharacterData* SelectedCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWeaponData* SelectedWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UProjectileData* SelectedProjectile;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<UCharacterData*, int> CharactersLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<UWeaponData*, int> WeaponsLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<UProjectileData*, int> ProjectilesLevel;
};