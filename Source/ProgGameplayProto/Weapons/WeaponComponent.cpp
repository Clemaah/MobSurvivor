// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ProgGameplayProto/Characters/ProgGameplayProtoCharacter.h"
#include "ProgGameplayProto/Weapons/WeaponCharacteristics.h"
#include "ProgGameplayProto/Projectiles/ProjectileData.h"
#include "ProgGameplayProto/Projectiles/Projectile.h"
#include "ProgGameplayProto/Effects/ProjectileEffect.h"



//////////////////////////////////////////////////////////////////////////
// --- INITIALIZATION
UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWeaponComponent::InitializeWeapon(AProgGameplayProtoCharacter* NewCharacter, const FWeaponCharacteristics InWeaponCharacteristics, const FProjectileCharacteristics InProjectileCharacteristics)
{
	Character = NewCharacter;
	WeaponCharacteristics = InWeaponCharacteristics;
	ProjectileCharacteristics = InProjectileCharacteristics;
}


//////////////////////////////////////////////////////////////////////////
// --- BEHAVIOUR
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TryShooting(DeltaTime);
}

void UWeaponComponent::TryShooting(float DeltaTime)
{
	TimeElapsedSinceLastShoot += DeltaTime;

	if (!IsValid(Character)) return;

	if (!Character->WantsToShoot()) return;

	if (TimeElapsedSinceLastShoot >= GetShootDelay())
	{
		if (!isDoubleShotActivated && CanActivateDoubleShot())
		{
			isDoubleShotActivated = true;
			TimeElapsedSinceLastShoot = FMath::Max(0, GetShootDelay() - 0.1f);
		}

		Shoot();
	}
}

void UWeaponComponent::Shoot()
{
	if (!IsValid(Character->WeaponProjectileToSpawn)) return;

	TArray<FVector> shootDirections = ComputeSpreadDirections();

	for (int i = 0; i < shootDirections.Num(); i++)
	{
		SpawnProjectile(shootDirections[i]);
	}
}

bool UWeaponComponent::CanActivateDoubleShot()
{
	const float value = WeaponCharacteristics.DoubleShotChance;
	const float multiplier = Character->GetCharacteristics().DoubleShotChanceMultiplier;

	const float diceRoll = FMath::RandRange(0, 100);

	return diceRoll <= value * multiplier;
}

TArray<FVector> UWeaponComponent::ComputeSpreadDirections()
{
	TArray<FVector> directions;

	FVector centralDirection = GetMouseDirection();
	const int numberOfProjectiles = WeaponCharacteristics.ShotsNumber;

	if (numberOfProjectiles < 2)
	{
		centralDirection = centralDirection.RotateAngleAxis(GetPrecisionRandomAngle(), FVector::UpVector);
		directions.Add(centralDirection);
	}
	else
	{
		const float spread = GetSpread();
		const float angleIncrement = spread / (numberOfProjectiles - 1);

		for (int i = 0; i < numberOfProjectiles; i++)
		{
			float offsetAngle = (i * angleIncrement) - (spread / 2.0f);
			offsetAngle += GetPrecisionRandomAngle();
			FVector direction = centralDirection;
			direction = direction.RotateAngleAxis(offsetAngle, FVector::UpVector);

			directions.Add(direction);
		}
	}

	return directions;
}

void UWeaponComponent::SpawnProjectile(FVector Direction)
{
	const FVector spawnLocation = Character->GetActorLocation();
	const FRotator spawnRotation = FRotator::ZeroRotator;

	AProjectile* projectile = Character->GetWorld()->SpawnActor<AProjectile>(Character->WeaponProjectileToSpawn, spawnLocation, spawnRotation);

	projectile->InitializeProjectile(ProjectileCharacteristics, WeaponCharacteristics);

	if (Direction == FVector::ZeroVector)
		Direction = Character->GetActorForwardVector();

	projectile->SetDirection(Direction);

	for (int i = 0; i < Effects.Num(); i++)
	{
		Effects[i]->RegisterProjectile(projectile);
	}
}

FVector UWeaponComponent::GetMouseDirection()
{
	FVector mouseLocation;
	FVector mouseDirection;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->DeprojectMousePositionToWorld(mouseLocation, mouseDirection);

	FHitResult outHit;
	FVector endTraceLocation = mouseLocation + mouseDirection * 10000;
	FCollisionObjectQueryParams params;
	params.AddObjectTypesToQuery(ECC_WorldStatic);
	GetWorld()->LineTraceSingleByObjectType(outHit, mouseLocation, endTraceLocation, params);

	if (outHit.bBlockingHit)
	{
		FVector neutralCharacterLocation = Character->GetActorLocation();
		neutralCharacterLocation.Z = 0;
		FVector neutralMouseLocation = outHit.Location;
		neutralMouseLocation.Z = 0;

		FVector direction = neutralMouseLocation - neutralCharacterLocation;
		direction.Normalize();

		return direction;
	}

	return Character->GetActorForwardVector();
}

float UWeaponComponent::GetShootDelay()
{
	const float value = WeaponCharacteristics.FireRate;
	const float multiplier = Character->GetCharacteristics().FireRateMultiplier;

	return 1 / (value * multiplier);
}

float UWeaponComponent::GetPrecisionRandomAngle()
{
	const float totalPrecision = (WeaponCharacteristics.Precision) * Character->GetCharacteristics().PrecisionMultiplier;

	const float precisionFactor = FMath::Clamp((1 - totalPrecision), 0, 1);
	const float angleLimit = 30 * precisionFactor;

	const float angle = FMath::RandRange(-angleLimit, angleLimit);

	return angle;
}

float UWeaponComponent::GetSpread()
{
	const float value = WeaponCharacteristics.Spread;
	const float multiplier = Character->GetCharacteristics().SpreadMultiplier;

	return FMath::Clamp(value * multiplier, 0, 360);
}

void UWeaponComponent::UpdateCharacteristics(FWeaponCharacteristics& WeaponBonuses, FProjectileCharacteristics& ProjectileBonuses)
{
	WeaponCharacteristics += WeaponBonuses;
	ProjectileCharacteristics += ProjectileBonuses;
}

void UWeaponComponent::AddEffect(UProjectileEffect* Effect)
{
	Effects.Add(Effect);
}
