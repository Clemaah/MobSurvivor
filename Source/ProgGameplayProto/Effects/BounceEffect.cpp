// Fill out your copyright notice in the Description page of Project Settings.


#include "BounceEffect.h"

#include "ProgGameplayProto/Projectiles/Projectile.h"

void UBounceEffect::OnProjectileHit(AProjectile* Projectile, FVector HitLocation, FVector OriginLocation)
{
	Projectile->SetRandomDirection();

	Super::OnProjectileHit(Projectile, HitLocation, OriginLocation);
}
