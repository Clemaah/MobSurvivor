// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilityComponent.generated.h"

class UAbilityData;
class AProgGameplayProtoCharacter;
class AUpgradesManager;


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROGGAMEPLAYPROTO_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAbilityComponent();

protected:
	UPROPERTY()
	TObjectPtr<UAbilityData> AbilityData;

	UPROPERTY()
	TObjectPtr<AProgGameplayProtoCharacter> Character;

	TObjectPtr<AUpgradesManager> UpgradesManager;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void InitializeAbility(AProgGameplayProtoCharacter* NewCharacter);

	virtual void SetData(UAbilityData* Data) { AbilityData = Data; }

	virtual void UpdateAbility();

	virtual float GetMaxHealth();
	virtual float GetRegenerationRate();
	virtual float GetDropChance();
	virtual float GetDropMultiplier();
	virtual float GetDropCollectorRadius();
	virtual int GetNumberOfUpgrades();

public:
	float BonusMaxHealth = 0;
	float BonusRegenerationRate = 0;
	float BonusDropChance = 0;
	float BonusDropMultiplier = 0;
	float BonusDropCollectorRadius = 0;
	int BonusNumberOfUpgrades = 0;
};
