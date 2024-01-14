#pragma once

#include "CoreMinimal.h"
#include "ProjectileEffect.h"
#include "ZoneSlowEffect.generated.h"

UCLASS()
class PROGGAMEPLAYPROTO_API UZoneSlowEffect : public UProjectileEffect
{
	GENERATED_BODY()

	public:

		virtual void OnProjectileDestroy(AProjectile* Projectile) override;
};
