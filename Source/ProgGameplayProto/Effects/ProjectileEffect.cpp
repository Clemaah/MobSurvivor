// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileEffect.h"
#include "Logging/StructuredLog.h"
#include "ProgGameplayProto/Weapons/WeaponProjectile.h"

void UProjectileEffect::RegisterProjectile(AWeaponProjectile* Projectile)
{
	if (!IsValid(Projectile))
	{
		UE_LOGFMT(LogTemp, Error, "Projectile is not Valid");

		return;
	}

	CurrentProjectile = Projectile;

	CurrentProjectile->OnProjectileDestroy.AddDynamic(this, &UProjectileEffect::OnProjectileDestroy);
}

void UProjectileEffect::OnProjectileDestroy(AWeaponProjectile* Projectile)
{

}