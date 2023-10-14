// Fill out your copyright notice in the Description page of Project Settings.


#include "BounceEffect.h"

#include "ProgGameplayProto/Weapons/WeaponProjectile.h"

void UBounceEffect::RegisterProjectile(AWeaponProjectile* Projectile)
{
	Super::RegisterProjectile(Projectile);

	Projectile->NumberOfHitsBeforeDestroy += NumberOfAdditionalBounces;
}

void UBounceEffect::OnProjectileHit(AWeaponProjectile* Projectile, FVector HitLocation, FVector OriginLocation)
{
	Super::OnProjectileHit(Projectile, HitLocation, OriginLocation);

	Projectile->SetRandomDirection();
}
