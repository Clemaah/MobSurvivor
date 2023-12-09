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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ULevelData* GameLevelData;

	UPROPERTY(BlueprintReadOnly)
	AEnemySpawnerManager* EnemySpawnerManager;

	UPROPERTY(BlueprintReadOnly)
	ABonusManager* BonusManager;

protected:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
};