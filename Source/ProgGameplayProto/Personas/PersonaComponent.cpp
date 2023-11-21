// Fill out your copyright notice in the Description page of Project Settings.


#include "PersonaComponent.h"

#include "Kismet/GameplayStatics.h"
#include "ProgGameplayProto/Personas/PersonaData.h"
#include "ProgGameplayProto/ProgGameplayProtoCharacter.h"
#include "ProgGameplayProto/ProgGameplayProtoGameMode.h"
#include "ProgGameplayProto/HealthComponent.h"
#include "ProgGameplayProto/UpgradesManager.h"

class AProgGameplayProtoGameMode;

// Sets default values for this component's properties
UPersonaComponent::UPersonaComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UPersonaComponent::BeginPlay()
{
	Super::BeginPlay();
	UpgradesManager = Cast<AProgGameplayProtoGameMode, AGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->UpgradesManager;
}

void UPersonaComponent::InitializePersona(AProgGameplayProtoCharacter* NewCharacter)
{
	Character = NewCharacter;
	Character->GetHealth()->InitializeHealth(GetMaxHealth(), GetRegenerationRate());
	Character->SetDropCollectorRadius(GetDropCollectorRadius());
	UpgradesManager->NumberOfUpgrades = GetNumberOfUpgrades();
}

void UPersonaComponent::UpdatePersona()
{
	Character->GetHealth()->SetMaxHealth(GetMaxHealth());
	Character->GetHealth()->SetRegenerationRate(GetRegenerationRate());
	Character->SetDropCollectorRadius(GetDropCollectorRadius());
	UpgradesManager->NumberOfUpgrades = GetNumberOfUpgrades();
	//Character->(GetDropChance());
	//Character->(GetDropMultiplier());
}

// Called every frame
void UPersonaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

float UPersonaComponent::GetMaxHealth()
{
	if (!IsValid(PersonaData)) return 0.0f;

	float value = FMath::Clamp(PersonaData->MaxHealth + BonusMaxHealth, 10, 200);

	return value;
}

float UPersonaComponent::GetRegenerationRate()
{
	if (!IsValid(PersonaData)) return 0.0f;

	float value = FMath::Clamp(PersonaData->RegenerationRate + BonusRegenerationRate, 0, 1);

	return value;
}

float UPersonaComponent::GetDropChance()
{
	if (!IsValid(PersonaData)) return 0.0f;

	float value = FMath::Clamp(PersonaData->DropChance + BonusDropChance, 1, 100);

	return value;
}

float UPersonaComponent::GetCoinMultiplier()
{
	if (!IsValid(PersonaData)) return 0.0f;

	float value = FMath::Clamp(PersonaData->CoinMultiplier + BonusCoinMultiplier, 1, 5);

	return value;
}

float UPersonaComponent::GetExperienceMultiplier()
{
	if (!IsValid(PersonaData)) return 0.0f;

	float value = FMath::Clamp(PersonaData->ExperienceMultiplier + BonusExperienceMultiplier, 1, 5);

	return value;
}

float UPersonaComponent::GetDropCollectorRadius()
{
	if (!IsValid(PersonaData)) return 0.0f;

	float value = FMath::Clamp(PersonaData->DropCollectorRadius + BonusDropCollectorRadius, 50, 300);

	return value;
}

int UPersonaComponent::GetNumberOfUpgrades()
{
	if (!IsValid(PersonaData)) return 0.0f;

	int value = FMath::Clamp(PersonaData->NumberOfUpgrades + BonusNumberOfUpgrades, 1, 5);

	return value;
}