// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MobSurvivorGameState.generated.h"

/**
 *
 */
UCLASS()
class PROGGAMEPLAYPROTO_API AMobSurvivorGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AMobSurvivorGameState();

protected:
	float GameTime = 0;

	bool bHasGameStarted = false;

public:
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetGameTime() { return GameTime; }

	UFUNCTION(BlueprintCallable)
	virtual void StartGame();
};