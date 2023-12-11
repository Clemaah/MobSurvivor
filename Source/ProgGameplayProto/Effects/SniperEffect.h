#pragma once

#include "CoreMinimal.h"
#include "ProjectileHitEffect.h"
#include "SniperEffect.generated.h"

/**
 *
 */
UCLASS()
class PROGGAMEPLAYPROTO_API USniperEffect : public UProjectileHitEffect
{
	GENERATED_BODY()

public:
	int32 NumberOfEnemyToPierce;

public:
	virtual void RegisterProjectile(AProjectile* Projectile) override;
};
