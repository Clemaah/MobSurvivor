// Fill out your copyright notice in the Description page of Project Settings.


#include "MobSurvivorGameInstance.h"

#include "PlayerGPEData.h"
#include "ProgGameplayProto/System/MobSurvivorSaveGame.h"
#include "ProgGameplayProto/Projectiles/ProjectileData.h"
#include "ProgGameplayProto/Characters/PersonaData.h"
#include "ProgGameplayProto/Weapons/WeaponData.h"
#include "Kismet/GameplayStatics.h"

/**
 * 
 */
UMobSurvivorGameInstance::UMobSurvivorGameInstance()
{
	SaveName = "MobSurvivor";
	GamePlayElementsData = nullptr;
	SaveGameInstance = nullptr;
	SelectedPersona = nullptr;
	SelectedWeapon = nullptr;
	SelectedProjectile = nullptr;
    HttpManager = nullptr;
}

void UMobSurvivorGameInstance::OnStart()
{
    LoadGame();

    if (!UpdateData()) return;

    if(SaveGameInstance->PersonasCurrentLevel.Num() > 0)
		SelectedPersona = SaveGameInstance->PersonasCurrentLevel.begin()->Key;

    if (SaveGameInstance->WeaponsCurrentLevel.Num() > 0)
		SelectedWeapon = SaveGameInstance->WeaponsCurrentLevel.begin()->Key;

    if (SaveGameInstance->ProjectilesCurrentLevel.Num() > 0)
		SelectedProjectile = SaveGameInstance->ProjectilesCurrentLevel.begin()->Key;

    HttpManager = NewObject<UHttpManager>();
    HttpManager->OnTokenChangedDelegate.AddDynamic(this, &UMobSurvivorGameInstance::ChangePlayerToken);
}

void UMobSurvivorGameInstance::SaveGame()
{
    UE_LOG(LogTemp, Log, TEXT("Saving game..."));

    const bool IsSaved = UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveName, 0);

    LogResultOfSaveGame(IsSaved);

}

void UMobSurvivorGameInstance::NewSave()
{

    UE_LOG(LogTemp, Log, TEXT("No saved games found. Trying to save a new one."));

    SaveGameInstance = Cast<UMobSurvivorSaveGame>(UGameplayStatics::CreateSaveGameObject(UMobSurvivorSaveGame::StaticClass()));

    SaveGame();
}

void UMobSurvivorGameInstance::LoadGame()
{
    USaveGame* LoadedGame = UGameplayStatics::LoadGameFromSlot(SaveName, 0);
    SaveGameInstance = Cast<UMobSurvivorSaveGame>(LoadedGame);

    UE_LOG(LogTemp, Log, TEXT("Trying to load a saved game."));

    if (!IsValid(SaveGameInstance))
        NewSave();

    else
    {
	    UE_LOG(LogTemp, Log, TEXT("Saved game found. Loaded."));
    }
}

void UMobSurvivorGameInstance::LogResultOfSaveGame(const bool IsSaved)
{
    if (IsSaved)
    {
        UE_LOG(LogTemp, Log, TEXT("Game saved."));
    }

    else
    {
	    UE_LOG(LogTemp, Log, TEXT("Cannot save the game."));
    }
}

bool UMobSurvivorGameInstance::UpdateData()
{
    UE_LOG(LogTemp, Log, TEXT("Checking for update."));

    if (!IsValid(GamePlayElementsData))
    {
        UE_LOG(LogTemp, Log, TEXT("No update's data found."));
        return false;
    }

    // Adding new GamePlayElement Data
    for (auto& Element : GamePlayElementsData->Personas)
        SaveGameInstance->PersonasCurrentLevel.FindOrAdd(Element, 0);

    for (auto& Element : GamePlayElementsData->Weapons)
        SaveGameInstance->WeaponsCurrentLevel.FindOrAdd(Element, 0);

    for (auto& Element : GamePlayElementsData->Projectiles)
        SaveGameInstance->ProjectilesCurrentLevel.FindOrAdd(Element, 0);

    // Removing old GamePlayElement Data
    for(auto Iterator = SaveGameInstance->PersonasCurrentLevel.CreateIterator(); Iterator; ++Iterator)
    {
        if (GamePlayElementsData->Personas.Find(Iterator.Key()) == INDEX_NONE)
            Iterator.RemoveCurrent();
    }

    for (auto Iterator = SaveGameInstance->WeaponsCurrentLevel.CreateIterator(); Iterator; ++Iterator)
    {
        if (GamePlayElementsData->Weapons.Find(Iterator.Key()) == INDEX_NONE)
            Iterator.RemoveCurrent();
    }

    for (auto Iterator = SaveGameInstance->ProjectilesCurrentLevel.CreateIterator(); Iterator; ++Iterator)
    {
        if (GamePlayElementsData->Projectiles.Find(Iterator.Key()) == INDEX_NONE)
            Iterator.RemoveCurrent();
    }

    return true;
}



void UMobSurvivorGameInstance::LevelUpPersona(UPersonaData* Persona) const
{
    if (CanPersonaLevelUp(Persona))
        SaveGameInstance->PersonasCurrentLevel[Persona] += 1;
}

void UMobSurvivorGameInstance::LevelUpWeapon(UWeaponData* Weapon) const
{
    if (CanWeaponLevelUp(Weapon))
        SaveGameInstance->WeaponsCurrentLevel[Weapon] += 1;
}

void UMobSurvivorGameInstance::LevelUpProjectile(UProjectileData* Projectile) const
{
    if (CanProjectileLevelUp(Projectile))
        SaveGameInstance->ProjectilesCurrentLevel[Projectile] += 1;
}



int UMobSurvivorGameInstance::GetNextPersonaLevelPrice(UPersonaData* Persona) const
{
    if (!IsValid(Persona))
        return -1;

    return Persona->GetLevelPrice(GetPersonaCurrentLevel(Persona) + 1);
}

int UMobSurvivorGameInstance::GetNextWeaponLevelPrice(UWeaponData* Weapon) const
{
    if (!IsValid(Weapon))
        return -1;

    return Weapon->GetLevelPrice(GetWeaponCurrentLevel(Weapon) + 1);
}

int UMobSurvivorGameInstance::GetNextProjectileLevelPrice(UProjectileData* Projectile) const
{
    if (!IsValid(Projectile))
        return -1;

    return Projectile->GetLevelPrice(GetProjectileCurrentLevel(Projectile) + 1);
}



int UMobSurvivorGameInstance::GetPersonaCurrentLevel(UPersonaData* Persona) const
{
    if (!IsValid(Persona))
        return -1;

    return SaveGameInstance->PersonasCurrentLevel[Persona];
}

int UMobSurvivorGameInstance::GetWeaponCurrentLevel(UWeaponData* Weapon) const
{
    if (!IsValid(Weapon))
        return -1;

    return SaveGameInstance->WeaponsCurrentLevel[Weapon];
}

int UMobSurvivorGameInstance::GetProjectileCurrentLevel(UProjectileData* Projectile) const
{
    if (!IsValid(Projectile))
        return -1;

    return SaveGameInstance->ProjectilesCurrentLevel[Projectile];
}



bool UMobSurvivorGameInstance::CanPersonaLevelUp(UPersonaData* Persona) const
{
    if (!IsValid(Persona))
        return false;

    return (GetPersonaCurrentLevel(Persona) < Persona->Levels.Num() - 1);
}

bool UMobSurvivorGameInstance::CanWeaponLevelUp(UWeaponData* Weapon) const
{
    if (!IsValid(Weapon))
        return false;

    return (GetWeaponCurrentLevel(Weapon) < Weapon->Levels.Num() - 1);
}

bool UMobSurvivorGameInstance::CanProjectileLevelUp(UProjectileData* Projectile) const
{
    if (!IsValid(Projectile))
        return false;

    return (GetProjectileCurrentLevel(Projectile) < Projectile->Levels.Num() - 1);
}



bool UMobSurvivorGameInstance::HasEnoughCoinsToSpend(const int Quantity) const
{
    return (SaveGameInstance->TotalCoins >= Quantity);
}

void UMobSurvivorGameInstance::ChangeTotalCoinsBy(const int Quantity)
{
    SaveGameInstance->TotalCoins += Quantity;
    OnTotalCoinsChanged.Broadcast(SaveGameInstance->TotalCoins);
}

void UMobSurvivorGameInstance::ChangeTotalPointsBy(const int Quantity)
{
    SaveGameInstance->TotalPoints += Quantity;
}

void UMobSurvivorGameInstance::ChangePlayerToken(const FString& Token)
{
    SaveGameInstance->PlayerToken = Token;
    SaveGame();
}