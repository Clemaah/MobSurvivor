// Fill out your copyright notice in the Description page of Project Settings.


#include "ProgGameplayProtoGameState.h"

AProgGameplayProtoGameState::AProgGameplayProtoGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AProgGameplayProtoGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bHasGameStarted)
		GameTime += DeltaSeconds;

	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, "Game Time: " + FString::SanitizeFloat(GameTime));
}

void AProgGameplayProtoGameState::StartGame()
{
	bHasGameStarted = true;
}