// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileInteraction.h"

#include "ProgGameplayProto/Actors/Projectile.h"

// Sets default values for this component's properties
UProjectileInteraction::UProjectileInteraction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UProjectileInteraction::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UProjectileInteraction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UProjectileInteraction::HitByProjectile(AProjectile* Projectile)
{
	OnHitByProjectile.Broadcast(Projectile->GetActorRotation(), Projectile->GetCharacteristics().Speed);
}