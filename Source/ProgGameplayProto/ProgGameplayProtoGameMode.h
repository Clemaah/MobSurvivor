// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ProgGameplayProtoGameMode.generated.h"

class ABonusManager;
class AEnemySpawnerManager;
class UGameLevelData;

UCLASS(minimalapi)
class AProgGameplayProtoGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AProgGameplayProtoGameMode();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UGameLevelData* GameLevelData;

	UPROPERTY(BlueprintReadOnly)
	AEnemySpawnerManager* EnemySpawnerManager;

	UPROPERTY(BlueprintReadOnly)
	ABonusManager* BonusManager;

protected:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
};