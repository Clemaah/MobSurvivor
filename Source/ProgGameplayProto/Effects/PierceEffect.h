#pragma once

#include "CoreMinimal.h"
#include "ProjectileTransformEffect.h"
#include "PierceEffect.generated.h"

/**
 *
 */
UCLASS()
class PROGGAMEPLAYPROTO_API UPierceEffect : public UProjectileTransformEffect
{
	GENERATED_BODY()

public:
	virtual void OnProjectileHit(AProjectile* Projectile, FVector HitLocation, FVector OriginLocation) override;
};
