#include "SniperEffect.h"
#include "ProgGameplayProto/Projectiles/Projectile.h"

void USniperEffect::RegisterProjectile(AProjectile* Projectile)
{
	Super::RegisterProjectile(Projectile);
	Projectile->GetCharacteristics()->NumberOfHitsBeforeDestroy += NumberOfEnemyToPierce;
}
