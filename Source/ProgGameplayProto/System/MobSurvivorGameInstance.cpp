// Fill out your copyright notice in the Description page of Project Settings.


#include "MobSurvivorGameInstance.h"

#include "DefaultParametersData.h"
#include "ProgGameplayProto/System/MobSurvivorSaveGame.h"
#include "ProgGameplayProto/Projectiles/ProjectileData.h"
#include "ProgGameplayProto/Characters/CharacterData.h"
#include "ProgGameplayProto/Weapons/WeaponData.h"
#include "Kismet/GameplayStatics.h"

/**
 * 
 */
UMobSurvivorGameInstance::UMobSurvivorGameInstance()
{
    SaveName = "MobSurvivor";
	GamePoints = 0;
    FirstSaveParameters = nullptr;
    SaveGameInstance = nullptr;
    SelectedCharacter = nullptr;
    SelectedWeapon = nullptr;
    SelectedProjectile = nullptr;
}

void UMobSurvivorGameInstance::OnStart()
{
    LoadGame();

    if(SaveGameInstance->CharactersCurrentLevel.Num() > 0)
		SelectedCharacter = SaveGameInstance->CharactersCurrentLevel.begin()->Key;

    if (SaveGameInstance->WeaponsCurrentLevel.Num() > 0)
		SelectedWeapon = SaveGameInstance->WeaponsCurrentLevel.begin()->Key;

    if (SaveGameInstance->ProjectilesCurrentLevel.Num() > 0)
		SelectedProjectile = SaveGameInstance->ProjectilesCurrentLevel.begin()->Key;
}

void UMobSurvivorGameInstance::LoadGame()
{
    USaveGame* LoadedGame = UGameplayStatics::LoadGameFromSlot(SaveName, 0);
    SaveGameInstance = Cast<UMobSurvivorSaveGame>(LoadedGame);

    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Trying to load a saved game."));

    if (!IsValid(SaveGameInstance))
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("No saved games found. Trying to save a new one."));

        SaveGameInstance = Cast<UMobSurvivorSaveGame>(UGameplayStatics::CreateSaveGameObject(UMobSurvivorSaveGame::StaticClass()));

        if (!ResetSaveGameParameters())
            return;

        SaveGame();
    }

    else
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Saved game found. Loaded."));

}

void UMobSurvivorGameInstance::SaveGame()
{
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Saving game..."));

    const bool IsSaved = UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveName, 0);

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

bool UMobSurvivorGameInstance::ResetSaveGameParameters()
{

    if (!IsValid(FirstSaveParameters))
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("No default parameters found."));
        return false;
    }

    SaveGameInstance->TotalCoins = FirstSaveParameters->TotalCoins;
    SaveGameInstance->TotalPoints = FirstSaveParameters->TotalPoints;
    SaveGameInstance->PlayerToken = FirstSaveParameters->PlayerToken;
    SaveGameInstance->CharactersCurrentLevel = FirstSaveParameters->CharactersCurrentLevel;
    SaveGameInstance->WeaponsCurrentLevel = FirstSaveParameters->WeaponsCurrentLevel;
    SaveGameInstance->ProjectilesCurrentLevel = FirstSaveParameters->ProjectilesCurrentLevel;

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

void UMobSurvivorGameInstance::ChangeTotalCoinsBy(const int Quantity) const
{
    SaveGameInstance->TotalCoins += Quantity;
}

void UMobSurvivorGameInstance::AddGamePointsToTotal() const
{
    SaveGameInstance->TotalPoints += GamePoints;
}