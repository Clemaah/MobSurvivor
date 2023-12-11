#pragma once

#include "CoreMinimal.h"
#include "BonusData.h"
#include "ProgGameplayProto/Projectiles/ProjectileData.h"
#include "SniperBonusData.generated.h"

class USniperEffect;
/**
 *
 */
UCLASS()
class PROGGAMEPLAYPROTO_API USniperProjectileData : public UProjectileData
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USniperEffect> SniperEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NumberOfEnemyToPierce;

public:
	virtual void Apply(AProgGameplayProtoCharacter* Character, UWeaponComponent* Weapon) override;
};
