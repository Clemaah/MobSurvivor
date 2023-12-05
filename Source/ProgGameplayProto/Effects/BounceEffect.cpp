// Fill out your copyright notice in the Description page of Project Settings.


#include "BounceEffect.h"

#include "ProgGameplayProto/Projectiles/Projectile.h"

void UBounceEffect::RegisterProjectile(AProjectile* Projectile)
{
	Super::RegisterProjectile(Projectile);

	Projectile->GetCharacteristics()->NumberOfHitsBeforeDestroy += NumberOfAdditionalBounces;
}

void UBounceEffect::OnProjectileHit(AProjectile* Projectile, FVector HitLocation, FVector OriginLocation)
{
	Super::OnProjectileHit(Projectile, HitLocation, OriginLocation);

	Projectile->SetRandomDirection();
}
