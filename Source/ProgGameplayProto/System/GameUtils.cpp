// Fill out your copyright notice in the Description page of Project Settings.


#include "GameUtils.h"
#include "ProgGameplayProto/Characters/ProgGameplayProtoCharacter.h"
#include "ProgGameplayProto/System/MobSurvivorGameInstance.h"
#include "Kismet/GameplayStatics.h"

AProgGameplayProtoCharacter* UGameUtils::GetMainCharacter()
{
	return AProgGameplayProtoCharacter::Instance;
}

UMobSurvivorSaveGame* UGameUtils::GetSaveGame(UWorld* World)
{
	return Cast<UMobSurvivorGameInstance>(UGameplayStatics::GetGameInstance(World))->SaveGameInstance;
}