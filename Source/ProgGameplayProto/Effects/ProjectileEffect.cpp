// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileEffect.h"
#include "Logging/StructuredLog.h"
#include "ProgGameplayProto/Projectiles/Projectile.h"

void UProjectileEffect::RegisterProjectile(AProjectile* Projectile)
{
	if (!IsValid(Projectile))
	{
		UE_LOGFMT(LogTemp, Error, "Projectile is not Valid");

		return;
	}

	CurrentProjectile = Projectile;

	CurrentProjectile->OnProjectileDestroyDelegate.AddDynamic(this, &UProjectileEffect::OnProjectileDestroy);
}

void UProjectileEffect::OnProjectileDestroy(AProjectile* Projectile)
{

}