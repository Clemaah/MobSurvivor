// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileTransformEffect.h"
#include "BounceEffect.generated.h"

/**
 *
 */
UCLASS()
class PROGGAMEPLAYPROTO_API UBounceEffect : public UProjectileTransformEffect
{
	GENERATED_BODY()

public:
	virtual void OnProjectileHit(AProjectile* Projectile, FVector HitLocation, FVector OriginLocation) override;
};
