// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "ProgGameplayProto/DataAssets/Enemies/EnemyCharacteristics.h"
#include "ProgGameplayProto/DataAssets/PersonaCharacteristics.h"

#include "EnemyData.generated.h"



USTRUCT(BlueprintType)
struct PROGGAMEPLAYPROTO_API FEnemyLevel
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FPersonaCharacteristics PersonaCharacteristics;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FEnemyCharacteristics EnemyCharacteristics;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (ClampMin = 0))
	int Price;
};


UCLASS(BlueprintType)
class PROGGAMEPLAYPROTO_API UEnemyData : public UPrimaryDataAsset
{

	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meta")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meta", Meta = (MultiLine = true))
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Characteristics", Meta = (EditFixedOrder, ToolTip = "The first level contains base characteristics. Next ones contains modifiers."))
	TArray<FEnemyLevel> Levels;

	UEnemyData();

	UFUNCTION(BlueprintCallable)
	virtual FPersonaCharacteristics GetCurrentPersonaCharacteristics(const int Level);

	virtual FEnemyCharacteristics GetCurrentEnemyCharacteristics(const int Level);
};
