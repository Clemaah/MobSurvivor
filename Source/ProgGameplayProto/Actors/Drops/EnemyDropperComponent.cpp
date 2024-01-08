// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyDropperComponent.h"
#include "ProgGameplayProto/ActorComponents/HealthComponent.h"

void UEnemyDropperComponent::BeginPlay()
{
	Super::BeginPlay();

	SetupDropOnDie();
}

void UEnemyDropperComponent::SetupDropOnDie()
{
	UHealthComponent* health = GetOwner()->FindComponentByClass<UHealthComponent>();

	if (!IsValid(health)) return;

	health->OnBeforeHealthDie.AddDynamic(this, &UEnemyDropperComponent::OnEnemyDie);
}

void UEnemyDropperComponent::OnEnemyDie()
{
	Drop();
}