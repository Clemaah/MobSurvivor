// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MenuGameMode.generated.h"

class UScore;
class AUpgradesManager;
/**
 * 
 */
UCLASS()
class PROGGAMEPLAYPROTO_API AMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	AUpgradesManager* UpgradesManager;

	UFUNCTION(BlueprintImplementableEvent)
	void InsertScores(const TArray<UScore*>& Scores);

protected:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

};
