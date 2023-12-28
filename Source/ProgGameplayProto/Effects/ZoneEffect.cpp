#include "ZoneEffect.h"
#include "ProgGameplayProto/Projectiles/ProjectileData.h"
#include "Zone.h"
#include "ProgGameplayProto/Projectiles/Projectile.h"

void UZoneEffect::OnProjectileDestroy(AProjectile* Projectile)
{
	//Super::OnProjectileDestroy(Projectile);
	const FVector SpawnLocation = Projectile->GetActorLocation();
	GetWorld()->SpawnActor<AZone>(SpawnLocation, FRotator::ZeroRotator);

}
