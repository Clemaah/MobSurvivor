// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Iris/Core/IrisProfiler.h"
#include "DropperComponent.generated.h"

USTRUCT(BlueprintType)
struct FDropAndWeight
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ObjectToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Weight;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROGGAMEPLAYPROTO_API UDropperComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDropperComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FDropAndWeight> Drops;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D NumberOfDropsRange;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual AActor* SpawnWeightedDrop();

	virtual int32 GetWeightedIndex();

	virtual FVector GetRandomSpawnLocation();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Drop();
};
