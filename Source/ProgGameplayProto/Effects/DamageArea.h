// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProgGameplayProto/Drops/Drop.h"
#include "DamageArea.generated.h"

/**
 *
 */
UCLASS()
class PROGGAMEPLAYPROTO_API ADamageArea : public ADrop
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drop")
	int CoinAmount;

	virtual void Collect() override;
};
