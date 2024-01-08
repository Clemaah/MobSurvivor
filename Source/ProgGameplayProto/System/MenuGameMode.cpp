// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuGameMode.h"

#include "GameUtils.h"
#include "MobSurvivorGameInstance.h"
#include "Managers/HttpManager.h"

void AMenuGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	HttpManager = UGameUtils::GetGameInstance(GetWorld())->HttpManager;

	HttpManager->OnGetScoresDelegate.AddDynamic(this, &AMenuGameMode::GetScores);
	HttpManager->OnGetUserDelegate.AddDynamic(this, &AMenuGameMode::Connect);
	HttpManager->OnErrorDelegate.AddDynamic(this, &AMenuGameMode::DisplayError);
	HttpManager->OnMessageDelegate.AddDynamic(this, &AMenuGameMode::DisplayMessage);
}
