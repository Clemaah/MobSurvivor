// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileHitEffect.h"

#include "ProgGameplayProto/Weapons/WeaponProjectile.h"

void UProjectileHitEffect::RegisterProjectile(AWeaponProjectile* Projectile)
{
	Super::RegisterProjectile(Projectile);

	Projectile->OnProjectileHit.AddDynamic(this, &UProjectileHitEffect::OnProjectileHit);
}

void UProjectileHitEffect::OnProjectileHit(AWeaponProjectile* Projectile, FVector HitLocation, FVector OriginLocation)
{

}

void UProjectileHitEffect::OnProjectileDestroy(AWeaponProjectile* Projectile)
{
	Super::OnProjectileDestroy(Projectile);

	Projectile->OnProjectileHit.AddDynamic(this, &UProjectileHitEffect::OnProjectileHit);
}