// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "BonusManager.generated.h"

class UObjectLibrary;
class UBonusData;
/**
 *
 */
UCLASS()
class PROGGAMEPLAYPROTO_API ABonusManager : public AInfo
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<UBonusData*> AllBonuses;

	UPROPERTY()
	TArray<UBonusData*> AvailableBonuses;

protected:
	virtual void BeginPlay() override;

	virtual void LoadBonuses();

	UFUNCTION(BlueprintCallable)
	UBonusData* GetRandomBonus();

public:
	UPROPERTY(BlueprintReadOnly)
	int NumberOfUpgrades = 3;
};
