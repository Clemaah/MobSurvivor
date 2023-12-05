// Fill out your copyright notice in the Description page of Project Settings.


#include "MobSurvivorGameInstance.h"
#include "ProgGameplayProto/Framework/MobSurvivorSaveGame.h"
#include "Kismet/GameplayStatics.h"

UMobSurvivorGameInstance::UMobSurvivorGameInstance()
{
    SaveGameSlotName = "MobSurvivorSave";
}

void UMobSurvivorGameInstance::OnStart()
{
    LoadGame();
}

void UMobSurvivorGameInstance::LoadGame()
{
    USaveGame* LoadedGame = UGameplayStatics::LoadGameFromSlot(SaveGameSlotName, 0);
    SaveGameInstance = Cast<UMobSurvivorSaveGame>(LoadedGame);

    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Trying to load a saved game."));

    if (!SaveGameInstance)
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("No saved games found. Trying to save a new one."));

        SaveGameInstance = Cast<UMobSurvivorSaveGame>(UGameplayStatics::CreateSaveGameObject(UMobSurvivorSaveGame::StaticClass()));

        if(!IsValid(StartDataReference))
        {
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Save failed. No Default Data Ref Found."));
            return;
        }
        SaveGameInstance->ParametersToSave = StartDataReference->Parameters;
        const bool IsSaved = UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameSlotName, 0);

        LogResultOfSaveGame(IsSaved);
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Saved game found. Loaded."));
    }

}

void UMobSurvivorGameInstance::SaveGame()
{
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Saving game..."));

    const bool IsSaved = UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameSlotName, 0);

    LogResultOfSaveGame(IsSaved);

}

void UMobSurvivorGameInstance::LogResultOfSaveGame(const bool IsSaved)
{
    if (IsSaved)
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Game saved."));
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Cannot save the game."));
    }
}