// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PersonaData.generated.h"

/**
 * 
 */
UCLASS()
class PROGGAMEPLAYPROTO_API UPersonaData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Persona Data|Nom")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MultiLine = true), Category = "Persona Data|Description")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Persona Data|Health")
	float MaxHealth = 50;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Persona Data|Health")
	float RegenerationRate = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Persona Data|Drop")
	float DropChance = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Persona Data|Drop")
	float DropCollectorRadius = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Persona Data|Drop")
	float CoinMultiplier = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Persona Data|Drop")
	float ExperienceMultiplier = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Persona Data|Upgrade")
	int NumberOfUpgrades = 3;
};
