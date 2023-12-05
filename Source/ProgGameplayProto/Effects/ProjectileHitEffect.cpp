// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileHitEffect.h"

#include "ProgGameplayProto/Projectiles/Projectile.h"

void UProjectileHitEffect::RegisterProjectile(AProjectile* Projectile)
{
	Super::RegisterProjectile(Projectile);

	Projectile->OnProjectileHitDelegate.AddDynamic(this, &UProjectileHitEffect::OnProjectileHit);
}

void UProjectileHitEffect::OnProjectileHit(AProjectile* Projectile, FVector HitLocation, FVector OriginLocation)
{

}

void UProjectileHitEffect::OnProjectileDestroy(AProjectile* Projectile)
{
	Super::OnProjectileDestroy(Projectile);

	Projectile->OnProjectileHitDelegate.AddDynamic(this, &UProjectileHitEffect::OnProjectileHit);
}