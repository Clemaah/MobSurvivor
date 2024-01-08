// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Drop.generated.h"

class UDropperComponent;

UCLASS()
class PROGGAMEPLAYPROTO_API ADrop : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADrop();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drop")
	float CollectionSpeed = 1000;

	UPROPERTY()
	AActor* CollectingTarget;

	bool bIsBeingCollected = false;

	float CollectionSqrdDistance = 2500;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void MoveTowardCollectingTarget(float DeltaTime);

	virtual void Collect();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void StartCollection(AActor* NewTarget);
};