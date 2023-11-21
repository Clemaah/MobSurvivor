// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterAbilitiesData.generated.h"

/**
 * 
 */
UCLASS()
class PROGGAMEPLAYPROTO_API UCharacterAbilitiesData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities Data|Health")
	float MaxHealth = 50;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities Data|Health")
	float RegenerationRate = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities Data|Drop")
	float DropChance = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities Data|Drop")
	float DropMultiplier = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities Data|Drop")
	float DropCollectorRadius = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities Data|Upgrade")
	int NumberOfUpgrades = 3;
};
