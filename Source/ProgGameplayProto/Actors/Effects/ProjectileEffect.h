// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileEffect.generated.h"

class AProjectile;

/**
 *
 */
UCLASS()
class PROGGAMEPLAYPROTO_API UProjectileEffect : public UObject
{
	GENERATED_BODY()

public:
	virtual void RegisterProjectile(AProjectile* Projectile);

	UFUNCTION()
	virtual void OnProjectileHit(AProjectile* Projectile, FVector HitLocation, FVector OriginLocation);

	UFUNCTION()
	virtual void OnProjectileDestroy(AProjectile* Projectile);
};