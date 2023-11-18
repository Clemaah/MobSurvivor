// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "UpgradesManager.generated.h"

/**
 * 
 */
UCLASS()
class PROGGAMEPLAYPROTO_API AUpgradesManager : public AInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	int NumberOfUpgrades = 3;
};
