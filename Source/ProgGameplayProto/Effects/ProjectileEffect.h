// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ProjectileEffect.generated.h"

class AWeaponProjectile;

/**
 *
 */
UCLASS()
class PROGGAMEPLAYPROTO_API UProjectileEffect : public UObject
{
	GENERATED_BODY()

public:
	virtual void RegisterProjectile(AWeaponProjectile* Projectile);

	UFUNCTION()
	virtual void OnProjectileDestroy(AWeaponProjectile* Projectile);

protected:
	UPROPERTY()
	AWeaponProjectile* CurrentProjectile;
};
