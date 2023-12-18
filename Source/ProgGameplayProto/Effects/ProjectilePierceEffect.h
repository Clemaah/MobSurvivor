﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileEffect.h"
#include "ProjectilePierceEffect.generated.h"

/**
 *
 */
UCLASS()
class PROGGAMEPLAYPROTO_API UProjectilePierceEffect : public UProjectileEffect
{
	GENERATED_BODY()

public:
	virtual void OnProjectileHit(AProjectile* Projectile, FVector HitLocation, FVector OriginLocation) override;
};