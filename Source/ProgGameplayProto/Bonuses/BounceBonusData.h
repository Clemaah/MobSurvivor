// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BonusData.h"
#include "BounceBonusData.generated.h"

class UBounceEffect;
/**
 *
 */
UCLASS()
class PROGGAMEPLAYPROTO_API UBounceBonusData : public UBonusData
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBounceEffect> BounceEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NumberOfBounces;

public:
	virtual void Apply(AProgGameplayProtoCharacter* Character, UWeaponComponent* Weapon, UPersonaComponent* Persona) override;
};
