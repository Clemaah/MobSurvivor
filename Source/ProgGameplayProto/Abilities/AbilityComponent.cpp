// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityComponent.h"
#include "ProgGameplayProto/Abilities/AbilityData.h"
#include "ProgGameplayProto/ProgGameplayProtoCharacter.h"

// Sets default values for this component's properties
UAbilityComponent::UAbilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAbilityComponent::InitializeAbility(AProgGameplayProtoCharacter* NewCharacter)
{
	Character = NewCharacter;
}

float UAbilityComponent::GetMaxHealth()
{
	if (!IsValid(AbilityData)) return 0.0f;

	float value = FMath::Clamp(AbilityData->MaxHealth + BonusMaxHealth, 10, 200);

	return value;
}

float UAbilityComponent::GetRegenerationRate()
{
	if (!IsValid(AbilityData)) return 0.0f;

	float value = FMath::Clamp(AbilityData->RegenerationRate + BonusRegenerationRate, 0, 1);

	return value;
}

float UAbilityComponent::GetDropChance()
{
	if (!IsValid(AbilityData)) return 0.0f;

	float value = FMath::Clamp(AbilityData->DropChance + BonusDropChance, 1, 100);

	return value;
}

float UAbilityComponent::GetDropMultiplier()
{
	if (!IsValid(AbilityData)) return 0.0f;

	float value = FMath::Clamp(AbilityData->DropMultiplier + BonusDropMultiplier, 1, 5);

	return value;
}

float UAbilityComponent::GetPickUpDistance()
{
	if (!IsValid(AbilityData)) return 0.0f;

	float value = FMath::Clamp(AbilityData->PickUpDistance + BonusPickUpDistance, 50, 300);

	return value;
}

int UAbilityComponent::GetUpgradesNumber()
{
	if (!IsValid(AbilityData)) return 0.0f;

	int value = FMath::Clamp(AbilityData->UpgradesNumber + BonusUpgradesNumber, 3, 5);

	return value;
}