// Fill out your copyright notice in the Description page of Project Settings.


#include "PierceEffect.h"

#include "ProgGameplayProto/Projectiles/Projectile.h"

void UPierceEffect::OnProjectileHit(AProjectile* Projectile, FVector HitLocation, FVector OriginLocation)
{
	Super::OnProjectileHit(Projectile, HitLocation, OriginLocation);
}
