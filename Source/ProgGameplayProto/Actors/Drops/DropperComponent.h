// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "DropperComponent.generated.h"

class ADrop;

UENUM(BlueprintType)
enum EDropType { Coin, Experience, Heal, Upgrade };

USTRUCT(BlueprintType)
struct FDropAndWeight
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ADrop> ObjectToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EDropType> Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D NumberOfDropsRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ClampMin = 0, ClampMax = 100))
	float ChanceToDrop;
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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual FVector GetRandomSpawnLocation();

public:
	virtual void Drop();
};
