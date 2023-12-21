#pragma once

#include "CoreMinimal.h"
#include "ProjectileEffect.h"
#include "Zone.h"
#include "ZoneEffect.generated.h"

UCLASS()
class PROGGAMEPLAYPROTO_API UZoneEffect : public UProjectileEffect
{
	GENERATED_BODY()

	public:
		virtual void OnProjectileDestroy(AProjectile* Projectile) override;

	protected:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zone")
		TSubclassOf<AZone> ZoneToSpawn;
};
