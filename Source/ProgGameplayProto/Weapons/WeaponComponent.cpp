// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "ProgGameplayProto/Weapons/WeaponData.h"
#include "ProgGameplayProto/ProgGameplayProtoCharacter.h"
#include "ProgGameplayProto/Weapons/WeaponProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "ProgGameplayProto/Effects/ProjectileEffect.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TryShooting(DeltaTime);
}

void UWeaponComponent::InitializeWeapon(AProgGameplayProtoCharacter* NewCharacter, UWeaponData* Data)
{
	WeaponData = Data;
	Character = NewCharacter;
}

void UWeaponComponent::TryShooting(float DeltaTime)
{
	TimeElapsedSinceLastShoot += DeltaTime;

	if (!IsValid(Character)) return;

	if (!Character->WantsToShoot()) return;

	if (TimeElapsedSinceLastShoot >= GetShootDelay())
	{
		TimeElapsedSinceLastShoot = 0;

		Shoot();
	}
}

void UWeaponComponent::AddEffect(UProjectileEffect* Effect)
{
	Effects.Add(Effect);
}

void UWeaponComponent::Shoot()
{
	if (!IsValid(Character)) return;
	if (!IsValid(Character->WeaponProjectileToSpawn)) return;

	TArray<FVector> shootDirections = ComputeSpreadDirections();

	for (int i = 0; i < shootDirections.Num(); i++)
	{
		SpawnProjectile(shootDirections[i]);
	}
}

void UWeaponComponent::SpawnProjectile(FVector Direction)
{
	const FVector spawnLocation = Character->GetActorLocation();
	const FRotator spawnRotation = FRotator::ZeroRotator;

	AWeaponProjectile* projectile = Character->GetWorld()->SpawnActor<AWeaponProjectile>(Character->WeaponProjectileToSpawn, spawnLocation, spawnRotation);

	projectile->SetParameters(GetProjectileSize(), GetProjectileRange(), GetProjectileSpeed(), GetDamages(), GetCriticalHitChance(), GetCriticalHitDamagesMultiplier());

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

TArray<FVector> UWeaponComponent::ComputeSpreadDirections()
{
	TArray<FVector> directions;

	FVector centralDirection = GetMouseDirection();
	const int32 numberOfProjectiles = GetNumberOfProjectiles();

	if (numberOfProjectiles < 2)
	{
		centralDirection = centralDirection.RotateAngleAxis(GetPrecisionRandomAngle(), FVector::UpVector);
		directions.Add(centralDirection);
	}
	else
	{
		const float angleIncrement = GetSpread() / (numberOfProjectiles - 1);
		const float spread = GetSpread();

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

int32 UWeaponComponent::GetNumberOfProjectiles()
{
	if (!IsValid(WeaponData)) return int32();

	int32 output = static_cast<int32>(WeaponData->NumberOfShots + BonusNumberOfShots) * (WeaponData->NumberOfShotsMultiplier + BonusNumberOfShotsMultiplier);
	output = FMath::Max(0, output);

	return output;
}

float UWeaponComponent::GetShootDelay()
{
	if (!IsValid(WeaponData)) return 0.0f;

	float value = FMath::Max(0.1f, (WeaponData->FireRate + BonusFireRate));
	float multiplier = FMath::Max(0.1f, WeaponData->FireRateMultiplier + BonusFireRateMultiplier);

	return 1 / (value * multiplier);
}

float UWeaponComponent::GetProjectileSize()
{
	if (!IsValid(WeaponData)) return 0.0f;

	float value = FMath::Max(0.1f, WeaponData->ProjectileSize + BonusProjectileSize);
	float multiplier = FMath::Max(0.1f, WeaponData->ProjectileSizeMultiplier + BonusProjectileSizeMultiplier);

	return value * multiplier;
}

float UWeaponComponent::GetProjectileRange()
{
	if (!IsValid(WeaponData)) return 0.0f;

	float value = FMath::Max(100, WeaponData->Range + BonusRange);
	float multiplier = FMath::Max(0.1f, WeaponData->RangeMultiplier + BonusRangeMultiplier);

	float output = FMath::Max(100, value * multiplier);

	return output;
}

float UWeaponComponent::GetProjectileSpeed()
{
	if (!IsValid(WeaponData)) return 0.0f;

	float value = FMath::Max(50, WeaponData->ProjectileSpeed + BonusProjectileSpeed);
	float multiplier = FMath::Max(0.1f, WeaponData->ProjectileSpeedMultiplier + BonusProjectileSpeedMultiplier);

	float output = FMath::Max(50, value * multiplier);

	return output;
}

float UWeaponComponent::GetSpread()
{
	if (!IsValid(WeaponData)) return 0.0f;

	return (WeaponData->Spread + BonusSpread) * (WeaponData->SpreadMultiplier + BonusSpreadMultiplier);
}

float UWeaponComponent::GetPrecisionRandomAngle()
{
	if (!IsValid(WeaponData)) return 0.0f;

	const float totalPrecision = (WeaponData->Precision + BonusPrecision) * (WeaponData->PrecisionMultiplier + BonusPrecisionMultiplier);

	const float precisionFactor = FMath::Clamp((1 - totalPrecision), 0, 1);
	const float angleLimit = 30 * precisionFactor;

	const float angle = FMath::RandRange(-angleLimit, angleLimit);

	return angle;
}

float UWeaponComponent::GetDamages()
{
	if (!IsValid(WeaponData)) return 0.0f;

	float output = (WeaponData->Damages + BonusDamages) * (WeaponData->DamagesMultiplier + BonusDamagesMultiplier);
	output = FMath::Max(0.1f, output);

	return output;
}

float UWeaponComponent::GetCriticalHitChance()
{
	if (!IsValid(WeaponData)) return 0.0f;

	return (WeaponData->CriticalHitChance + BonusCriticalHitChance) * (WeaponData->CriticalHitChanceMultiplier + BonusCriticalHitChanceMultiplier);
}

float UWeaponComponent::GetCriticalHitDamagesMultiplier()
{
	if (!IsValid(WeaponData)) return 0.0f;

	float output = WeaponData->CriticalHitDamageMultiplier + BonusCriticalHitDamageMultiplier;
	output = FMath::Max(1, output);

	return output;
}

