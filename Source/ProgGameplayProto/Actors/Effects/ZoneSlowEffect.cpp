#include "ZoneSlowEffect.h"
#include "SlowZone.h"
#include "ProgGameplayProto/Actors/Projectile.h"

void UZoneSlowEffect::OnProjectileDestroy(AProjectile* Projectile)
{
	//Super::OnProjectileDestroy(Projectile);
	const FVector SpawnLocation = Projectile->GetActorLocation();
	GetWorld()->SpawnActor<ASlowZone>(SpawnLocation, FRotator::ZeroRotator);

}
