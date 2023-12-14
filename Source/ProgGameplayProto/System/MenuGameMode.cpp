// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuGameMode.h"

#include "GameUtils.h"
#include "MobSurvivorGameInstance.h"
#include "ProgGameplayProto/Managers/UpgradesManager.h"

void AMenuGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	UpgradesManager = GetWorld()->SpawnActor<AUpgradesManager>();

	UGameUtils::GetGameInstance(GetWorld())->HttpManager->OnGetScoresDelegate.AddDynamic(this, &AMenuGameMode::InsertScores);
}