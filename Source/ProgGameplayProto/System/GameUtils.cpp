// Fill out your copyright notice in the Description page of Project Settings.


#include "GameUtils.h"
#include "ProgGameplayProto/Characters/ProgGameplayProtoCharacter.h"
#include "ProgGameplayProto/System/MobSurvivorGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include <regex>

AProgGameplayProtoCharacter* UGameUtils::GetMainCharacter()
{
	return AProgGameplayProtoCharacter::Instance;
}

UMobSurvivorGameInstance* UGameUtils::GetGameInstance(const UWorld* World)
{
	return Cast<UMobSurvivorGameInstance>(UGameplayStatics::GetGameInstance(World));
}

UMobSurvivorSaveGame* UGameUtils::GetSaveGame(const UWorld* World)
{
	return GetGameInstance(World)->SaveGameInstance;
}

bool UGameUtils::IsAValidEmail(const FString& Email)
{
	const std::regex pattern("^(([^<>()[\\]\\.,;:\\s@\"]+(\\.[^<>()[\\]\\.,;:\\s@\"]+)*)|(\".+\"))@((\\[[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\])|(([a-zA-Z\\-0-9]+\\.)+[a-zA-Z]{2,}))$");
	//const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

	return std::regex_match(TCHAR_TO_UTF8(*Email), pattern);;
}