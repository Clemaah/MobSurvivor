// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PersonaComponent.generated.h"

class UPersonaData;
class AProgGameplayProtoCharacter;
class AUpgradesManager;


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROGGAMEPLAYPROTO_API UPersonaComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPersonaComponent();

protected:
	UPROPERTY()
	TObjectPtr<UPersonaData> PersonaData;

	UPROPERTY()
	TObjectPtr<AProgGameplayProtoCharacter> Character;

	TObjectPtr<AUpgradesManager> UpgradesManager; // A modifier

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void InitializePersona(AProgGameplayProtoCharacter* NewCharacter);

	virtual void SetData(UPersonaData* Data) { PersonaData = Data; }

	virtual void UpdatePersona();

	virtual float GetMaxHealth();
	virtual float GetRegenerationRate();
	virtual float GetDropChance();
	virtual float GetCoinMultiplier();
	virtual float GetExperienceMultiplier();
	virtual float GetDropCollectorRadius();
	virtual int GetNumberOfUpgrades();

public:
	float BonusMaxHealth = 0;
	float BonusRegenerationRate = 0;
	float BonusDropChance = 0;
	float BonusCoinMultiplier = 0;
	float BonusExperienceMultiplier = 0;
	float BonusDropCollectorRadius = 0;
	int BonusNumberOfUpgrades = 0;
};
