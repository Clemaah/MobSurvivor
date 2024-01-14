// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ProgGameplayProto/DataAssets/Levels/LevelData.h"
#include "MobSurvivorGameMode.generated.h"

class ABonusManager;
class AEnemiesManager;
class ULevelData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFloatDelegateSignature, const float, value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIntDelegateSignature, const int, value);
/**
 *
 */
UCLASS(minimalapi)
class AMobSurvivorGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMobSurvivorGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ULevelData* GameLevelData;

	UPROPERTY(BlueprintReadOnly)
	AEnemiesManager* EnemiesManager;

	UPROPERTY(BlueprintReadOnly)
	ABonusManager* BonusManager;

protected:
	float GameTime = 0;

	float GameSecond = 0;

	UPROPERTY(BlueprintReadOnly)
	int GameCoins = 0;

	UPROPERTY(BlueprintReadOnly)
	int GamePoints = 0;

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

public:
	UPROPERTY(BlueprintAssignable)
	FIntDelegateSignature OnCoinsChanged;

	UPROPERTY(BlueprintAssignable)
	FIntDelegateSignature OnPointsChanged;

	UPROPERTY(BlueprintAssignable)
	FFloatDelegateSignature OnTimerChanged;

	UFUNCTION(BlueprintImplementableEvent)
	void OnWin();

	UFUNCTION(BlueprintImplementableEvent)
	void OnLoose();

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetGameTime() const { return GameTime; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetLevelDuration() const { return GameLevelData->Duration; }

	UFUNCTION(BlueprintCallable, Category = "MobSurvivor|SaveSettings")
	void ChangeGameCoinsBy(const int Quantity);

	UFUNCTION(BlueprintCallable, Category = "MobSurvivor|SaveSettings")
	void ChangeGamePointsBy(const int Quantity);
};