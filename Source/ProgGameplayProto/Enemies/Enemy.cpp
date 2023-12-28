// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "EnemyData.h"
#include "Components/CapsuleComponent.h"
#include "ProgGameplayProto/HealthComponent.h"
#include "ProgGameplayProto/Characters/PersonaData.h"
#include "ProgGameplayProto/Drops/EnemyDropperComponent.h"
#include "ProgGameplayProto/Projectiles/ProjectileData.h"
#include "ProgGameplayProto/Weapons/WeaponComponent.h"
#include "ProgGameplayProto/Weapons/WeaponData.h"

//////////////////////////////////////////////////////////////////////////
// --- INITIALIZATION

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = false;

	Collision = CreateDefaultSubobject<UCapsuleComponent>("Collision");
	SetRootComponent(Collision);

	Health = CreateDefaultSubobject<UHealthComponent>("Health");

	Weapon = CreateDefaultSubobject<UWeaponComponent>("Weapon");

	Dropper = CreateDefaultSubobject<UEnemyDropperComponent>("Dropper");
	Dropper->SetupAttachment(Collision);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	SetupComponents();
	Health->OnHealthDie.AddDynamic(this, &AEnemy::Die);
}

void AEnemy::ChangeDirection(FVector Target)
{
	Direction = Target - GetActorLocation();
	Direction.Z = 0;
	Direction.Normalize();
}

void AEnemy::Move(float DeltaTime, FVector PlayerPosition)
{
	if(EnemyData->IsTargettingPlayer)
		ChangeDirection(PlayerPosition);

	if((GetActorLocation() - PlayerPosition).Size() < EnemyData->MinDistanceToShoot)
		Weapon->bWantsToShoot = true;

	else
	{
		const FVector movement = Direction * Speed * DeltaTime;
		AddActorWorldOffset(movement);
		Weapon->bWantsToShoot = false;
	}
}

void AEnemy::Die()
{
	DieDelegate.Broadcast(this);
}

void AEnemy::SetupComponents()
{
	PersonaCharacteristics = EnemyData->PersonaData->GetCurrentCharacteristics(0);
	Weapon->InitializeWeapon(this, &PersonaCharacteristics, EnemyData->WeaponData->GetCurrentCharacteristics(0), EnemyData->ProjectileData->GetCurrentCharacteristics(0), EnemyData->ProjectileData->Effects);

	InitializeEnnemyVariables(); 
}

void AEnemy::InitializeEnnemyVariables()
{
	Health->InitializeHealth(PersonaCharacteristics.MaxHealth, PersonaCharacteristics.RegenerationRate);
	Speed = PersonaCharacteristics.Speed * 1000;
}