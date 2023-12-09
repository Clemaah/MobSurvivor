// Fill out your copyright notice in the Description page of Project Settings.


#include "MobSurvivorGameState.h"

AMobSurvivorGameState::AMobSurvivorGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMobSurvivorGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bHasGameStarted)
		GameTime += DeltaSeconds;

	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, "Game Time: " + FString::SanitizeFloat(GameTime));
}

void AMobSurvivorGameState::StartGame()
{
	bHasGameStarted = true;
}