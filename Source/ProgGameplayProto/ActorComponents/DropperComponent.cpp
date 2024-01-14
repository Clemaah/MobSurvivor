// Fill out your copyright notice in the Description page of Project Settings.


#include "DropperComponent.h"

#include "ProgGameplayProto/Actors/Drops/Drop.h"
#include "ProgGameplayProto/System/GameUtils.h"
#include "ProgGameplayProto/Actors/MobSurvivorCharacter.h"

class AMobSurvivorCharacter;
// Sets default values for this component's properties
UDropperComponent::UDropperComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDropperComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UDropperComponent::Drop()
{
	if (Drops.Num() < 1) return;

	const AMobSurvivorCharacter* mainCharacter = UGameUtils::GetMainCharacter();

	for (int32 i = 0; i < Drops.Num(); i++)
	{
		const float rolledDice = FMath::FRandRange(0.f, 100.f);
		float dropChance = Drops[i].ChanceToDrop;
		int32 numberOfDrops = FMath::RandRange(Drops[i].NumberOfDropsRange.X, Drops[i].NumberOfDropsRange.Y);

		switch (Drops[i].Type)
		{
			case Coin:
				dropChance *= mainCharacter->GetCharacterCharacteristics().CoinDropChanceMultiplier;
				numberOfDrops *= mainCharacter->GetCharacterCharacteristics().CoinMultiplier;
				break;

			case Experience:
				numberOfDrops *= mainCharacter->GetCharacterCharacteristics().ExperienceMultiplier;
				break;

			case Chest:
				dropChance *= mainCharacter->GetCharacterCharacteristics().UpgradeDropChanceMultiplier;
				break;

			default:
				break;
		}

		if (rolledDice <= dropChance)
		{
			for (int32 j = 0; j < numberOfDrops; j++)
			{
				FVector spawnLocation = GetRandomSpawnLocation();
				GetWorld()->SpawnActor<ADrop>(Drops[i].ObjectToSpawn, spawnLocation, FRotator::ZeroRotator);
			}
		}
	}
}

FVector UDropperComponent::GetRandomSpawnLocation()
{
	const FVector randomOffset = FVector(FMath::FRandRange(-20.0f, 20.0f), FMath::FRandRange(-20.0f, 20.0f), 0);

	const FVector output = GetComponentLocation() + randomOffset;

	return output;
}