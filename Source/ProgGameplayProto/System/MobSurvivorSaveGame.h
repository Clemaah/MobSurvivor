// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MobSurvivorParameters.h"
#include "UObject/ObjectMacros.h"

#include "MobSurvivorSaveGame.generated.h"

class UDefaultParametersData;
class UProjectileData;
class UWeaponData;
class UCharacterData;
/**
 * 
 */
UCLASS()
class PROGGAMEPLAYPROTO_API UMobSurvivorSaveGame : public USaveGame
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MobSurvivorSaveGame", Meta = (ShowOnlyInnerProperties))
	UDefaultParametersData* DefaultParameters;

public:
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void UseDefaultParameters();

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void LevelUpSelectedCharacter();
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void LevelUpSelectedWeapon();
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void LevelUpSelectedProjectile();

	UFUNCTION(BlueprintPure, Category = "SaveGame")
	bool CanSelectedCharacterLevelUp();
	UFUNCTION(BlueprintPure, Category = "SaveGame")
	bool CanSelectedWeaponLevelUp();
	UFUNCTION(BlueprintPure, Category = "SaveGame")
	bool CanSelectedProjectileLevelUp();

	UFUNCTION(BlueprintPure, Category = "SaveGame")
	bool HasEnoughMoneyToSpend(const int Quantity) const;

	UFUNCTION(BlueprintPure, Category = "SaveGame")
	int GetSelectedCharacterLevel();
	UFUNCTION(BlueprintPure, Category = "SaveGame")
	int GetSelectedWeaponLevel();
	UFUNCTION(BlueprintPure, Category = "SaveGame")
	int GetSelectedProjectileLevel();

	UFUNCTION(BlueprintPure, Category = "SaveGame")
	int GetSelectedCharacterNextLevelPrice();
	UFUNCTION(BlueprintPure, Category = "SaveGame")
	int GetSelectedWeaponNextLevelPrice();
	UFUNCTION(BlueprintPure, Category = "SaveGame")
	int GetSelectedProjectileNextLevelPrice();

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void AddCoins(const int Quantity);
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void SubtractCoins(const int Quantity);

	UPROPERTY(BlueprintReadWrite, Category = "MobSurvivorSaveGame", Meta = (ShowOnlyInnerProperties))
	FMobSurvivorParameters ParametersToSave;
};