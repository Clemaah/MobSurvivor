#pragma once

#include "CoreMinimal.h"
#include "ProjectileEffect.h"
#include "ZoneEffect.generated.h"

UCLASS()
class PROGGAMEPLAYPROTO_API UZoneEffect : public UProjectileEffect
{
	GENERATED_BODY()

	public:

		virtual void OnProjectileDestroy(AProjectile* Projectile) override;
};
