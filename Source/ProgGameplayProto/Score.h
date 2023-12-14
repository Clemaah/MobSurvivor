// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Score.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class PROGGAMEPLAYPROTO_API UScore : public UObject
{
	GENERATED_BODY()

public:
	UScore() : Score(0) {}

	void Initialization(const FString& inPseudo, const FString& inCharacter, const FString& InWeapon, const FString& InProjectile, float InScore);

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
