// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "UObject/ObjectMacros.h"

#include "MobSurvivorSaveGame.generated.h"

class UProjectileData;
class UWeaponData;
class UPersonaData;
/**
 * 
 */
UCLASS()
class PROGGAMEPLAYPROTO_API UMobSurvivorSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SavedParameters")
	int TotalCoins;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SavedParameters")
	int TotalPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SavedParameters")
	FString PlayerToken;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SavedParameters")
	TMap<UPersonaData*, int> PersonasCurrentLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SavedParameters")
	TMap<UWeaponData*, int> WeaponsCurrentLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SavedParameters")
	TMap<UProjectileData*, int> ProjectilesCurrentLevel;


	UMobSurvivorSaveGame() : TotalCoins(0), TotalPoints(0), PlayerToken("") {}
};