// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MobSurvivorGameMode.generated.h"

class ABonusManager;
class AEnemySpawnerManager;
class ULevelData;

UCLASS(minimalapi)
class AMobSurvivorGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMobSurvivorGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ULevelData* GameLevelData;

	UPROPERTY(BlueprintReadOnly)
	AEnemySpawnerManager* EnemySpawnerManager;

	UPROPERTY(BlueprintReadOnly)
	ABonusManager* BonusManager;

protected:
	float GameTime = 0;

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnWin();

	UFUNCTION(BlueprintImplementableEvent)
	void OnLoose();

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetGameTime() const { return GameTime; }

	UFUNCTION(BlueprintPure)
	float GetCurrentProgressionPercentage() const;
};