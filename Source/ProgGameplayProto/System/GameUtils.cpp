// Fill out your copyright notice in the Description page of Project Settings.


#include "GameUtils.h"
#include "ProgGameplayProto/System/MobSurvivorGameInstance.h"
#include "ProgGameplayProto/System/MobSurvivorGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "regex"

#include "ProgGameplayProto/Actors/MobSurvivorCharacter.h"


AMobSurvivorCharacter* UGameUtils::GetMainCharacter()
{
	return AMobSurvivorCharacter::Instance;
}

UMobSurvivorGameInstance* UGameUtils::GetGameInstance(const UWorld* World)
{
	return Cast<UMobSurvivorGameInstance>(UGameplayStatics::GetGameInstance(World));
}

AMobSurvivorGameMode* UGameUtils::GetGameMode(const UWorld* World)
{
	return Cast<AMobSurvivorGameMode>(UGameplayStatics::GetGameMode(World));
}

AMenuGameMode* UGameUtils::GetMenuGameMode(const UWorld* World)
{
	return Cast<AMenuGameMode>(UGameplayStatics::GetGameMode(World));
}

bool UGameUtils::IsAValidEmail(const FString& Email)
{
	const std::regex pattern("^(([^<>()[\\]\\.,;:\\s@\"]+(\\.[^<>()[\\]\\.,;:\\s@\"]+)*)|(\".+\"))@((\\[[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\])|(([a-zA-Z\\-0-9]+\\.)+[a-zA-Z]{2,}))$");

	return std::regex_match(TCHAR_TO_UTF8(*Email), pattern);;
}