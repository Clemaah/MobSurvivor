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

	UPROPERTY(VisibleAnywhere)
	TArray<UBonusData*> AllBonuses;

	UPROPERTY(VisibleAnywhere)
	TArray<UBonusData*> AvailableBonuses;

	UPROPERTY(VisibleAnywhere)
	TMap<UBonusData*, int> HeldBonus;

protected:
	virtual void BeginPlay() override;

	void LoadBonuses();

	int GetWeightedIndex();

public:
	UPROPERTY(BlueprintReadOnly)
	int NumberOfUpgrades = 3;

	UFUNCTION(BlueprintCallable)
	void ResetAvailableBonuses();

	UFUNCTION(BlueprintPure)
	UBonusData* GetRandomBonus();

	UFUNCTION(BlueprintPure)
	int GetBonusLevel(const UBonusData* Bonus);

	UFUNCTION(BlueprintCallable)
	void AddToHeldBonuses(UBonusData* Bonus);
};
