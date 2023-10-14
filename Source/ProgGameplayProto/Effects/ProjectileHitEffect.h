// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileEffect.h"
#include "ProjectileHitEffect.generated.h"

/**
 *
 */
UCLASS()
class PROGGAMEPLAYPROTO_API UProjectileHitEffect : public UProjectileEffect
{
	GENERATED_BODY()

public:
	virtual void RegisterProjectile(AWeaponProjectile* Projectile) override;

	UFUNCTION()
	virtual void OnProjectileHit(AWeaponProjectile* Projectile, FVector HitLocation, FVector OriginLocation);

	virtual void OnProjectileDestroy(AWeaponProjectile* Projectile) override;
};
