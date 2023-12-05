// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MenuGameMode.generated.h"

class UMenuData;
class AUpgradesManager;
/**
 * 
 */
UCLASS()
class PROGGAMEPLAYPROTO_API AMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMenuData* MenuData;

	UPROPERTY(BlueprintReadOnly)
	AUpgradesManager* UpgradesManager;

protected:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
};
