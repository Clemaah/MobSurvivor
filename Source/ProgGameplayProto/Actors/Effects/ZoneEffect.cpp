#include "ZoneEffect.h"
#include "Zone.h"
#include "ProgGameplayProto/Actors/Projectile.h"

void UZoneEffect::OnProjectileDestroy(AProjectile* Projectile)
{
	//Super::OnProjectileDestroy(Projectile);
	const FVector SpawnLocation = Projectile->GetActorLocation();
	GetWorld()->SpawnActor<AZone>(SpawnLocation, FRotator::ZeroRotator);

}
