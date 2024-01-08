// Fill out your copyright notice in the Description page of Project Settings.


#include "Drop.h"

// Sets default values
ADrop::ADrop()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADrop::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADrop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveTowardCollectingTarget(DeltaTime);
}

void ADrop::MoveTowardCollectingTarget(float DeltaTime)
{
	if (!bIsBeingCollected) return;

	FVector direction = CollectingTarget->GetActorLocation() - GetActorLocation();
	const float CurrentDistanceSqrt = direction.SquaredLength();

	float MoveAmountSqrt = CollectionSpeed * DeltaTime;
	MoveAmountSqrt *= MoveAmountSqrt;

	if (CurrentDistanceSqrt - MoveAmountSqrt < CollectionSqrdDistance)
	{
		Collect();
	}
	else
	{
		direction.Normalize();

		const FVector movement = direction * CollectionSpeed * DeltaTime;

		AddActorWorldOffset(movement);
	}
}

void ADrop::StartCollection(AActor* NewTarget)
{
	if (!IsValid(NewTarget)) return;

	CollectingTarget = NewTarget;

	bIsBeingCollected = true;
}

void ADrop::Collect()
{

}