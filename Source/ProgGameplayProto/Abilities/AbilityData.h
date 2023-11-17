// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AbilityData.generated.h"

/**
 * 
 */
UCLASS()
class PROGGAMEPLAYPROTO_API UAbilityData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Data|Health")
	float MaxHealth = 50;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Data|Health")
	float RegenerationRate = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Data|Drop")
	float DropChance = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Data|Drop")
	float DropMultiplier = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Data|Drop")
	float PickUpDistance = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Data|Upgrade")
	int UpgradesNumber = 3;
};
