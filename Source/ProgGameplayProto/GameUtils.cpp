// Fill out your copyright notice in the Description page of Project Settings.


#include "GameUtils.h"

#include "Characters/ProgGameplayProtoCharacter.h"
#include "Framework/MobSurvivorGameInstance.h"
#include "Kismet/GameplayStatics.h"

AProgGameplayProtoCharacter* UGameUtils::GetMainCharacter()
{
	return AProgGameplayProtoCharacter::Instance;
}

UMobSurvivorSaveGame* UGameUtils::GetSaveGame(UWorld* World)
{
	return Cast<UMobSurvivorGameInstance>(UGameplayStatics::GetGameInstance(World))->SaveGameInstance;
}