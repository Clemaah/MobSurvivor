// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "Components/CapsuleComponent.h"
#include "Drops/EnemyDropperComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProgGameplayProto/ActorComponents/HealthComponent.h"
#include "ProgGameplayProto/ActorComponents/WeaponComponent.h"
#include "ProgGameplayProto/DataAssets/Characters/CharacterData.h"
#include "ProgGameplayProto/DataAssets/Enemies/EnemyData.h"
#include "ProgGameplayProto/DataAssets/Projectiles/ProjectileData.h"
#include "ProgGameplayProto/DataAssets/Weapons/WeaponData.h"

//////////////////////////////////////////////////////////////////////////
// --- INITIALIZATION

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = false;

	Collision = CreateDefaultSubobject<UCapsuleComponent>("Collision");
	SetRootComponent(Collision);

	Dropper = CreateDefaultSubobject<UEnemyDropperComponent>("Dropper");
	Dropper->SetupAttachment(Collision);

	Health = CreateDefaultSubobject<UHealthComponent>("Health");
	Weapon = CreateDefaultSubobject<UWeaponComponent>("Weapon");
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	SetupComponents();
	Health->OnHealthDie.AddDynamic(this, &AEnemy::Die);
}

void AEnemy::SetupComponents()
{
	PersonaCharacteristics = EnemyData->GetCurrentPersonaCharacteristics(0);
	EnemyCharacteristics = EnemyData->GetCurrentEnemyCharacteristics(0);
	Weapon->InitializeWeapon(this, &PersonaCharacteristics, WeaponData->GetCurrentCharacteristics(0), ProjectileData->GetCurrentCharacteristics(0), ProjectileData->ProjectileToSpawn, ProjectileData->Effects);
	Health->InitializeHealth(PersonaCharacteristics.MaxHealth, PersonaCharacteristics.RegenerationRate);

	InitializeEnemyVariables();
}

void AEnemy::InitializeEnemyVariables()
{
	Rotation = GetActorRotation();
	Location = GetActorLocation();
	Location.Z = 0;

	MovingSpeed = PersonaCharacteristics.Speed * 1000;
	MovingDirection = GetActorForwardVector();
}

void AEnemy::Move(const float DeltaTime)
{
	AddActorWorldOffset(MovingSpeed * DeltaTime * MovingDirection);

	Location = GetActorLocation();
	Location.Z = 0;
}

void AEnemy::Rotate(const float DeltaTime, const FVector& PlayerPosition)
{
	RotationTarget = UKismetMathLibrary::FindLookAtRotation(Location, PlayerPosition);
	Rotation = UKismetMathLibrary::RInterpTo(Rotation, RotationTarget, DeltaTime, 2.5);

	SetActorRotation(Rotation);
}

void AEnemy::RunnerBehave(const float DeltaTime, const float PlayerDistanceSqrd)
{

	Move(DeltaTime);

	if (Weapon->bCanShoot && PlayerDistanceSqrd <= EnemyCharacteristics.DistanceToShootSqrd)
		Weapon->Shoot(Rotation);
}

void AEnemy::AggressiveBehave(const float DeltaTime, const float PlayerDistanceSqrd)
{
	if (PlayerDistanceSqrd > EnemyCharacteristics.DistanceToShootSqrd)
	{
		MovingDirection = GetActorForwardVector();
		Move(DeltaTime);

		return;
	}

	if (PlayerDistanceSqrd <= EnemyCharacteristics.DistanceToRecedeSqrd)
	{
		MovingDirection = -GetActorForwardVector();
		Move(DeltaTime);
	}

	if (Weapon->bCanShoot)
		Weapon->Shoot(Rotation);
}

void AEnemy::Behave(const float DeltaTime, const FVector& PlayerPosition)
{
	const float PlayerDistanceSqrd = UKismetMathLibrary::Vector_DistanceSquared(Location, PlayerPosition);

	Rotate(DeltaTime, PlayerPosition);

	if (!EnemyCharacteristics.IsTargetingPlayer)
	{
		RunnerBehave(DeltaTime, PlayerDistanceSqrd);

		return;
	}

	AggressiveBehave(DeltaTime, PlayerDistanceSqrd);
}

void AEnemy::Die()
{
	DieDelegate.Broadcast(this);
}