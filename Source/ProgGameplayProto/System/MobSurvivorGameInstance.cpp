// Fill out your copyright notice in the Description page of Project Settings.


#include "MobSurvivorGameInstance.h"

#include "MobSurvivorSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/HttpManager.h"
#include "ProgGameplayProto/DataAssets/Characters/CharacterData.h"
#include "ProgGameplayProto/DataAssets/DataList/PlayerDataListData.h"
#include "ProgGameplayProto/DataAssets/Projectiles/ProjectileData.h"
#include "ProgGameplayProto/DataAssets/Weapons/WeaponData.h"

/**
 * 
 */
UMobSurvivorGameInstance::UMobSurvivorGameInstance()
{
	SaveName = "MobSurvivor";
	GamePlayElementsData = nullptr;
	SaveGameInstance = nullptr;
	SelectedCharacter = nullptr;
	SelectedWeapon = nullptr;
	SelectedProjectile = nullptr;
    HttpManager = nullptr;
}

void UMobSurvivorGameInstance::OnStart()
{
    LoadGame();

    if (!UpdateData()) return;

    if(SaveGameInstance->CharactersCurrentLevel.Num() > 0)
		SelectedCharacter = SaveGameInstance->CharactersCurrentLevel.begin()->Key;

    if (SaveGameInstance->WeaponsCurrentLevel.Num() > 0)
		SelectedWeapon = SaveGameInstance->WeaponsCurrentLevel.begin()->Key;

    if (SaveGameInstance->ProjectilesCurrentLevel.Num() > 0)
		SelectedProjectile = SaveGameInstance->ProjectilesCurrentLevel.begin()->Key;

}

void UMobSurvivorGameInstance::InitializeHTTP(AMenuGameMode* GameMode)
{
    if (!IsValid(HttpManager))
        HttpManager = NewObject<UHttpManager>();

    HttpManager->Initialize(this, GameMode);
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
    for (auto& Element : GamePlayElementsData->Characters)
        SaveGameInstance->CharactersCurrentLevel.FindOrAdd(Element, 0);

    for (auto& Element : GamePlayElementsData->Weapons)
        SaveGameInstance->WeaponsCurrentLevel.FindOrAdd(Element, 0);

    for (auto& Element : GamePlayElementsData->Projectiles)
        SaveGameInstance->ProjectilesCurrentLevel.FindOrAdd(Element, 0);

    // Removing old GamePlayElement Data
    for(auto Iterator = SaveGameInstance->CharactersCurrentLevel.CreateIterator(); Iterator; ++Iterator)
    {
        if (GamePlayElementsData->Characters.Find(Iterator.Key()) == INDEX_NONE)
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



void UMobSurvivorGameInstance::LevelUpCharacter(UCharacterData* Character) const
{
    if (CanCharacterLevelUp(Character))
        SaveGameInstance->CharactersCurrentLevel[Character] += 1;
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



int UMobSurvivorGameInstance::GetNextCharacterLevelPrice(UCharacterData* Character) const
{
    if (!IsValid(Character))
        return -1;

    return Character->GetLevelPrice(GetCharacterCurrentLevel(Character) + 1);
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



int UMobSurvivorGameInstance::GetCharacterCurrentLevel(UCharacterData* Character) const
{
    if (!IsValid(Character))
        return -1;

    return SaveGameInstance->CharactersCurrentLevel[Character];
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



bool UMobSurvivorGameInstance::CanCharacterLevelUp(UCharacterData* Character) const
{
    if (!IsValid(Character))
        return false;

    return (GetCharacterCurrentLevel(Character) < Character->Levels.Num() - 1);
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

void UMobSurvivorGameInstance::UpdatePlayerToken(FString Token)
{
    SaveGameInstance->PlayerToken = Token;
    SaveGame();
}