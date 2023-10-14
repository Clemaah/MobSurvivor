// Fill out your copyright notice in the Description page of Project Settings.


#include "DropperComponent.h"

#include "Logging/StructuredLog.h"

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

AActor* UDropperComponent::SpawnWeightedDrop()
{
	if (Drops.Num() < 1) return nullptr;

	AActor* spawnedActor = nullptr;

	const int32 dropIndex = GetWeightedIndex();
	FVector spawnLocation = GetRandomSpawnLocation();

	AActor* spawnedDrop = GetWorld()->SpawnActor<AActor>(Drops[dropIndex].ObjectToSpawn, spawnLocation, FRotator::ZeroRotator);

	return spawnedDrop;
}

int32 UDropperComponent::GetWeightedIndex()
{
	float totalWeight = 0;

	for (int32 i = 0; i < Drops.Num(); i++)
	{
		totalWeight += Drops[i].Weight;
	}

	const float randomSelectedWeight = FMath::FRandRange(0, totalWeight);
	float weightsSum = 0;

	for (int32 i = 0; i < Drops.Num(); i++)
	{
		weightsSum += Drops[i].Weight;

		if (randomSelectedWeight <= weightsSum)
			return i;
	}

	UE_LOGFMT(LogTemp, Warning, "Should have found a weight in the list");

	return 0;
}

FVector UDropperComponent::GetRandomSpawnLocation()
{
	FVector randomOffset = FVector(FMath::FRandRange(-20.0f, 20.0f), FMath::FRandRange(-20.0f, 20.0f), 0);

	FVector output = GetComponentLocation() + randomOffset;

	return output;
}


// Called every frame
void UDropperComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDropperComponent::Drop()
{
	const int32 numberOfDrops = FMath::RandRange(NumberOfDropsRange.X, NumberOfDropsRange.Y);

	for (int32 i = 0; i < numberOfDrops; i++)
	{
		SpawnWeightedDrop();
	}
}