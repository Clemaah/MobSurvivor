// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Drop.h"
#include "CoinDrop.generated.h"

/**
 * 
 */
UCLASS()
class PROGGAMEPLAYPROTO_API ACoinDrop : public ADrop
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drop")
	int CoinAmount;

	virtual void Collect() override;
};