// Fill out your copyright notice in the Description page of Project Settings.


#include "ExperienceComponent.h"

// Sets default values for this component's properties
UExperienceComponent::UExperienceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UExperienceComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	CurrentLevelExperienceTarget = ExperienceCurve->GetFloatValue(CurrentLevel);

	OnLevelUp.Broadcast(CurrentLevel, CurrentLevelExperienceTarget);
	OnExperienceChanged.Broadcast(CurrentExperience);
}


// Called every frame
void UExperienceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UExperienceComponent::AddExperience(float Amount)
{
	CurrentExperience += Amount;

	if (CurrentExperience >= CurrentLevelExperienceTarget)
		LevelUp();
	else
		OnExperienceChanged.Broadcast(CurrentExperience);
}

void UExperienceComponent::LevelUp()
{
	CurrentExperience -= CurrentLevelExperienceTarget;

	CurrentLevel++;

	CurrentLevelExperienceTarget = ExperienceCurve->GetFloatValue(CurrentLevel);

	OnLevelUp.Broadcast(CurrentLevel, CurrentLevelExperienceTarget);
	OnExperienceChanged.Broadcast(CurrentExperience);
}