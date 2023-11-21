// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitiesComponent.h"

#include "Kismet/GameplayStatics.h"
#include "ProgGameplayProto/Abilities/AbilitiesData.h"
#include "ProgGameplayProto/ProgGameplayProtoCharacter.h"
#include "ProgGameplayProto/HealthComponent.h"
#include "ProgGameplayProto/ProgGameplayProtoGameMode.h"
#include "ProgGameplayProto/UpgradesManager.h"

// Sets default values for this component's properties
UAbilitiesComponent::UAbilitiesComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAbilitiesComponent::BeginPlay()
{
	Super::BeginPlay();


	UpgradesManager = Cast<AProgGameplayProtoGameMode, AGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->UpgradesManager;
}


// Called every frame
void UAbilitiesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAbilitiesComponent::InitializeAbilities(AProgGameplayProtoCharacter* NewCharacter)
{
	Character = NewCharacter;
	Character->GetHealth()->InitializeHealth(GetMaxHealth(), GetRegenerationRate());
	Character->SetDropCollectorRadius(GetDropCollectorRadius());
	UpgradesManager->NumberOfUpgrades = GetNumberOfUpgrades();
}

void UAbilitiesComponent::UpdateAbilities()
{
	Character->GetHealth()->SetMaxHealth(GetMaxHealth());
	Character->GetHealth()->SetRegenerationRate(GetRegenerationRate());
	Character->SetDropCollectorRadius(GetDropCollectorRadius());
	UpgradesManager->NumberOfUpgrades = GetNumberOfUpgrades();
	//Character->(GetDropChance());
	//Character->(GetDropMultiplier());
}

float UAbilitiesComponent::GetMaxHealth()
{
	if (!IsValid(AbilitiesData)) return 0.0f;

	float value = FMath::Clamp(AbilitiesData->MaxHealth + BonusMaxHealth, 10, 200);

	return value;
}

float UAbilitiesComponent::GetRegenerationRate()
{
	if (!IsValid(AbilitiesData)) return 0.0f;

	float value = FMath::Clamp(AbilitiesData->RegenerationRate + BonusRegenerationRate, 0, 1);

	return value;
}

float UAbilitiesComponent::GetDropChance()
{
	if (!IsValid(AbilitiesData)) return 0.0f;

	float value = FMath::Clamp(AbilitiesData->DropChance + BonusDropChance, 1, 100);

	return value;
}

float UAbilitiesComponent::GetDropMultiplier()
{
	if (!IsValid(AbilitiesData)) return 0.0f;

	float value = FMath::Clamp(AbilitiesData->DropMultiplier + BonusDropMultiplier, 1, 5);

	return value;
}

float UAbilitiesComponent::GetDropCollectorRadius()
{
	if (!IsValid(AbilitiesData)) return 0.0f;

	float value = FMath::Clamp(AbilitiesData->DropCollectorRadius + BonusDropCollectorRadius, 50, 300);

	return value;
}

int UAbilitiesComponent::GetNumberOfUpgrades()
{
	if (!IsValid(AbilitiesData)) return 0.0f;

	int value = FMath::Clamp(AbilitiesData->NumberOfUpgrades + BonusNumberOfUpgrades, 1, 5);

	return value;
}