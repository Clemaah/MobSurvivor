// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "ProgGameplayProto/Actors/Projectile.h"
#include "ProgGameplayProto/DataAssets/PersonaCharacteristics.h"


//////////////////////////////////////////////////////////////////////////
// --- INITIALIZATION
UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bHasAlreadyDoubleShot = false;
	bCanShoot = true;
	PersonaCharacteristics = nullptr;
}

void UWeaponComponent::InitializeWeapon(APawn* InPawn, FPersonaCharacteristics* InPersonaCharacteristics, const FWeaponCharacteristics InWeaponCharacteristics, const FProjectileCharacteristics InProjectileCharacteristics, const TSubclassOf<AProjectile> InProjectileToSpawn, const TArray<TSubclassOf<UProjectileEffect>> ProjectileEffects)
{
	Pawn = InPawn;
	PersonaCharacteristics = InPersonaCharacteristics;
	WeaponCharacteristics = InWeaponCharacteristics;
	ProjectileCharacteristics = InProjectileCharacteristics;
	Effects = ProjectileEffects;
	WeaponProjectileToSpawn = InProjectileToSpawn;
}


//////////////////////////////////////////////////////////////////////////
// --- BEHAVIOUR
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Reload(DeltaTime);
}

void UWeaponComponent::Reload(float DeltaTime)
{
	if(bCanShoot) return;

	if (!IsValid(Pawn)) return;

	TimeElapsedSinceLastShoot += DeltaTime;

	if (TimeElapsedSinceLastShoot < GetShootDelay()) return;

	bCanShoot = true;
	TimeElapsedSinceLastShoot = 0;
}

void UWeaponComponent::Shoot(FRotator Rotation)
{
	if (!IsValid(WeaponProjectileToSpawn)) return;

	TArray<FVector> shootDirections = ComputeSpreadDirections(Rotation);

	for (int i = 0; i < shootDirections.Num(); i++)
	{
		SpawnProjectile(shootDirections[i]);
	}

	TryDoubleShoot();

	bCanShoot = false;
}

void UWeaponComponent::TryDoubleShoot()
{
	if (bHasAlreadyDoubleShot)
		bHasAlreadyDoubleShot = false;

	else if (ActivateDoubleShot())
	{
		bHasAlreadyDoubleShot = true;
		TimeElapsedSinceLastShoot = FMath::Max(0, GetShootDelay() - 0.1f);
	}
}

bool UWeaponComponent::ActivateDoubleShot()
{
	const float value = WeaponCharacteristics.DoubleShotChance;
	const float multiplier = PersonaCharacteristics->DoubleShotChanceMultiplier;

	const float diceRoll = FMath::RandRange(0, 100);

	return diceRoll <= value * multiplier;
}

TArray<FVector> UWeaponComponent::ComputeSpreadDirections(FRotator Rotation)
{
	TArray<FVector> directions;
	FVector centralDirection = Rotation.Vector();

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
	if (Direction == FVector::ZeroVector)
		Direction = Pawn->GetActorForwardVector();

	const FVector spawnLocation = Pawn->GetActorLocation() + Direction * 60;

	AProjectile* projectile = Pawn->GetWorld()->SpawnActor<AProjectile>(WeaponProjectileToSpawn, spawnLocation, Direction.Rotation());

	projectile->InitializeProjectile(WeaponCharacteristics, ProjectileCharacteristics, Effects);

	projectile->SetDirection(Direction);
}

float UWeaponComponent::GetShootDelay()
{
	const float value = WeaponCharacteristics.FireRate;
	const float multiplier = PersonaCharacteristics->FireRateMultiplier;

	return 1 / (value * multiplier);
}

float UWeaponComponent::GetPrecisionRandomAngle()
{
	const float totalPrecision = (WeaponCharacteristics.Precision) * PersonaCharacteristics->PrecisionMultiplier;

	const float precisionFactor = FMath::Clamp((1 - totalPrecision), 0, 1);
	const float angleLimit = 30 * precisionFactor;

	const float angle = FMath::RandRange(-angleLimit, angleLimit);

	return angle;
}

float UWeaponComponent::GetSpread()
{
	const float value = WeaponCharacteristics.Spread;
	const float multiplier = PersonaCharacteristics->SpreadMultiplier;

	return FMath::Clamp(value * multiplier, 0, 360);
}

void UWeaponComponent::UpdateCharacteristics(FWeaponCharacteristics& WeaponBonuses, FProjectileCharacteristics& ProjectileBonuses)
{
	WeaponCharacteristics += WeaponBonuses;
	ProjectileCharacteristics += ProjectileBonuses;
}

void UWeaponComponent::AddEffect(TSubclassOf<UProjectileEffect> Effect)
{
	Effects.Add(Effect);
}
