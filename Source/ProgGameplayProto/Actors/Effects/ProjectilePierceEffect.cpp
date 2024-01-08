#include "ProjectilePierceEffect.h"

#include "ProgGameplayProto/Actors/Projectile.h"


void UProjectilePierceEffect::OnProjectileHit(AProjectile* Projectile, FVector HitLocation, FVector OriginLocation)
{
	Super::OnProjectileHit(Projectile, HitLocation, OriginLocation);

	Projectile->OnProjectileHitDelegate.RemoveAll(this);
	Projectile->OnProjectileDestroyDelegate.RemoveAll(this);

	Projectile->RemoveTransformEffect(this);
}
