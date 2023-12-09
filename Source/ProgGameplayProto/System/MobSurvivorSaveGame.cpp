// Fill out your copyright notice in the Description page of Project Settings.


#include "MobSurvivorSaveGame.h"
#include "DefaultParametersData.h"

void UMobSurvivorSaveGame::UseDefaultParameters()
{
	ParametersToSave = DefaultParameters->Parameters;
}

void UMobSurvivorSaveGame::LevelUpSelectedCharacter()
{
	if(CanSelectedCharacterLevelUp())
		ParametersToSave.CharactersLevel[ParametersToSave.SelectedCharacter] += 1;
}

void UMobSurvivorSaveGame::LevelUpSelectedWeapon()
{
	if (CanSelectedWeaponLevelUp())
		ParametersToSave.WeaponsLevel[ParametersToSave.SelectedWeapon] += 1;
}

void UMobSurvivorSaveGame::LevelUpSelectedProjectile()
{
	if (CanSelectedProjectileLevelUp())
		ParametersToSave.ProjectilesLevel[ParametersToSave.SelectedProjectile] += 1;
}


bool UMobSurvivorSaveGame::CanSelectedCharacterLevelUp()
{
	const UCharacterData* Character = ParametersToSave.SelectedCharacter;

	return (IsValid(Character) && GetSelectedCharacterLevel() < Character->Levels.Num() - 1);
}

bool UMobSurvivorSaveGame::CanSelectedWeaponLevelUp()
{
	const UWeaponData* Weapon = ParametersToSave.SelectedWeapon;

	return (IsValid(Weapon) && GetSelectedWeaponLevel() < Weapon->Levels.Num() - 1);
}

bool UMobSurvivorSaveGame::CanSelectedProjectileLevelUp()
{
	const UProjectileData* Projectile = ParametersToSave.SelectedProjectile;

	return (IsValid(Projectile) && GetSelectedProjectileLevel() < Projectile->Levels.Num() - 1);
}

bool UMobSurvivorSaveGame::HasEnoughMoneyToSpend(const int Quantity) const
{
	return ParametersToSave.TotalCoins >= Quantity;
}


int UMobSurvivorSaveGame::GetSelectedCharacterLevel() 
{
	return ParametersToSave.CharactersLevel[ParametersToSave.SelectedCharacter];
}

int UMobSurvivorSaveGame::GetSelectedWeaponLevel() 
{
	return ParametersToSave.WeaponsLevel[ParametersToSave.SelectedWeapon];
}

int UMobSurvivorSaveGame::GetSelectedProjectileLevel() 
{
	return ParametersToSave.ProjectilesLevel[ParametersToSave.SelectedProjectile];
}


int UMobSurvivorSaveGame::GetSelectedCharacterNextLevelPrice()
{
	return ParametersToSave.SelectedCharacter->GetLevelPrice(GetSelectedCharacterLevel() + 1);
}

int UMobSurvivorSaveGame::GetSelectedWeaponNextLevelPrice()
{
	return ParametersToSave.SelectedWeapon->GetLevelPrice(GetSelectedWeaponLevel() + 1);
}

int UMobSurvivorSaveGame::GetSelectedProjectileNextLevelPrice()
{
	return ParametersToSave.SelectedProjectile->GetLevelPrice(GetSelectedProjectileLevel() + 1);
}

void UMobSurvivorSaveGame::AddCoins(const int Quantity)
{
	ParametersToSave.TotalCoins += FMath::Abs(Quantity);
}

void UMobSurvivorSaveGame::SubtractCoins(const int Quantity)
{
	if (ParametersToSave.TotalCoins - Quantity < 0)
		return;

	ParametersToSave.TotalCoins -= FMath::Abs(Quantity);
}