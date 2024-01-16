// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Score.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct PROGGAMEPLAYPROTO_API FScore
{
	GENERATED_BODY()

	FScore() : Score(0) {}

	UPROPERTY(BlueprintReadOnly)
	FString Pseudo;

	UPROPERTY(BlueprintReadOnly)
	FString Character;

	UPROPERTY(BlueprintReadOnly)
	FString Weapon;

	UPROPERTY(BlueprintReadOnly)
	FString Projectile;

	UPROPERTY(BlueprintReadOnly)
	float Score;
};

/**
 *
 */
UCLASS(BlueprintType)
class PROGGAMEPLAYPROTO_API UScoreObject : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Initialization(const FScore& InScore);

	UPROPERTY(BlueprintReadOnly)
	FScore Score;
};
