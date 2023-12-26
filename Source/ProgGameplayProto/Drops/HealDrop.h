// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Drop.h"
#include "HealDrop.generated.h"

/**
 *
 */
UCLASS()
class PROGGAMEPLAYPROTO_API AHealDrop : public ADrop
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drop")
	float HealAmount;

	virtual void Collect() override;
};
