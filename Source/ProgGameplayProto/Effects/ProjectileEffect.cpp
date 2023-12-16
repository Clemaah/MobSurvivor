// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileEffect.h"
#include "ProgGameplayProto/Projectiles/Projectile.h"

void UProjectileEffect::RegisterProjectile(AProjectile* Projectile)
{
	if (!IsValid(Projectile))
	{
		UE_LOG(LogTemp, Error, TEXT("Projectile is not Valid"));

		return;
	}

	Projectile->OnProjectileHitDelegate.AddDynamic(this, &UProjectileEffect::OnProjectileHit);
	Projectile->OnProjectileDestroyDelegate.AddDynamic(this, &UProjectileEffect::OnProjectileDestroy);
}

void UProjectileEffect::OnProjectileHit(AProjectile* Projectile, FVector HitLocation, FVector OriginLocation)
{

}

void UProjectileEffect::OnProjectileDestroy(AProjectile* Projectile)
{

}