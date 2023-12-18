// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MenuGameMode.generated.h"

class UHttpManager;
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
	UHttpManager* HttpManager;

	UFUNCTION(BlueprintImplementableEvent)
	void GetScores(const TArray<UScore*>& Scores);

	UFUNCTION(BlueprintImplementableEvent)
	void Connect(const FString& Pseudo);

	UFUNCTION(BlueprintImplementableEvent)
	void DisplayError(const FString& Error);

	UFUNCTION(BlueprintImplementableEvent)
	void DisplayMessage(const FString& Message);

protected:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

};
