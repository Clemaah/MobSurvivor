// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DropperComponent.h"
#include "EnemyDropperComponent.generated.h"

/**
 *
 */
UCLASS()
class PROGGAMEPLAYPROTO_API UEnemyDropperComponent : public UDropperComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void SetupDropOnDie();

	UFUNCTION()
	virtual void OnEnemyDie();
};