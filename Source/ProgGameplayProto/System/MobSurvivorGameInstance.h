// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ProgGameplayProto/Managers/HTTPManager.h"
#include "MobSurvivorGameInstance.generated.h"

class UCharacterData;
class UWeaponData;
class UProjectileData;
class UGamePlayElementsData;
class UMobSurvivorSaveGame;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCoinsChangedSignature, const int, value);
/**
 * 
 */
UCLASS(ABSTRACT)
class PROGGAMEPLAYPROTO_API UMobSurvivorGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MobSurvivor|SaveSettings")
	FString SaveName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MobSurvivor|SaveSettings", Meta = (ShowOnlyInnerProperties))
	UGamePlayElementsData* GamePlayElementsData;

public:
	UPROPERTY(BlueprintAssignable)
	FCoinsChangedSignature OnTotalCoinsChanged;

	UPROPERTY(BlueprintReadOnly, Category = "MobSurvivor|SaveSettings")
	UMobSurvivorSaveGame* SaveGameInstance;

	UPROPERTY(BlueprintReadOnly, Category = "MobSurvivor|GameSettings")
	UHttpManager* HttpManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MobSurvivor|GameSettings")
	FString PlayerPseudo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MobSurvivor|GameSettings")
	UCharacterData* SelectedCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MobSurvivor|GameSettings")
	UWeaponData* SelectedWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MobSurvivor|GameSettings")
	UProjectileData* SelectedProjectile;




	UMobSurvivorGameInstance();

	virtual void OnStart() override;
	void NewSave();

	UFUNCTION(BlueprintCallable, Category = "MobSurvivor|SaveSettings")
	void LoadGame();
	
	UFUNCTION(BlueprintCallable, Category = "MobSurvivor|SaveSettings")
	void SaveGame();



	UFUNCTION(BlueprintCallable, Category = "MobSurvivor|SaveSettings")
	void LevelUpCharacter(UCharacterData* Character) const;

	UFUNCTION(BlueprintCallable, Category = "MobSurvivor|SaveSettings")
	void LevelUpWeapon(UWeaponData* Weapon) const;

	UFUNCTION(BlueprintCallable, Category = "MobSurvivor|SaveSettings")
	void LevelUpProjectile(UProjectileData* Projectile) const;


	UFUNCTION(BlueprintCallable, Category = "MobSurvivor|SaveSettings")
	int GetNextCharacterLevelPrice(UCharacterData* Character) const;

	UFUNCTION(BlueprintCallable, Category = "MobSurvivor|SaveSettings")
	int GetNextWeaponLevelPrice(UWeaponData* Weapon) const;

	UFUNCTION(BlueprintCallable, Category = "MobSurvivor|SaveSettings")
	int GetNextProjectileLevelPrice(UProjectileData* Projectile) const;


	UFUNCTION(BlueprintCallable, Category = "MobSurvivor|SaveSettings")
	int GetCharacterCurrentLevel(UCharacterData* Character) const;

	UFUNCTION(BlueprintCallable, Category = "MobSurvivor|SaveSettings")
	int GetWeaponCurrentLevel(UWeaponData* Weapon) const;

	UFUNCTION(BlueprintCallable, Category = "MobSurvivor|SaveSettings")
	int GetProjectileCurrentLevel(UProjectileData* Projectile) const;


	UFUNCTION(BlueprintCallable, Category = "MobSurvivor|SaveSettings")
	bool CanCharacterLevelUp(UCharacterData* Character) const;

	UFUNCTION(BlueprintCallable, Category = "MobSurvivor|SaveSettings")
	bool CanWeaponLevelUp(UWeaponData* Weapon) const;

	UFUNCTION(BlueprintCallable, Category = "MobSurvivor|SaveSettings")
	bool CanProjectileLevelUp(UProjectileData* Projectile) const;


	UFUNCTION(BlueprintCallable, Category = "MobSurvivor|SaveSettings")
	bool HasEnoughCoinsToSpend(const int Quantity) const;

	UFUNCTION(BlueprintCallable, Category = "MobSurvivor|SaveSettings")
	void ChangeTotalCoinsBy(const int Quantity);

	UFUNCTION(BlueprintCallable, Category = "MobSurvivor|SaveSettings")
	void ChangeTotalPointsBy(const int Quantity);

	UFUNCTION()
	void ChangePlayerToken(const FString& Token);


private:

	virtual bool UpdateData();

	void LogResultOfSaveGame(const bool IsSaved);
};