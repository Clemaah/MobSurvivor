// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ProgGameplayProto/ProjectileInteraction.h"
#include "ProgGameplayProto/Effects/ProjectileEffect.h"
#include "ProgGameplayProto/Effects/ProjectileTransformEffect.h"
#include "ProgGameplayProto/Weapons/WeaponCharacteristics.h"


//////////////////////////////////////////////////////////////////////////
// --- INITIALIZATION

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>("Collision");
	SetRootComponent(Collision);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Collision);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AProjectile::InitializeProjectile(const FWeaponCharacteristics& WeaponCharacteristics, const FProjectileCharacteristics& ProjectileCharacteristics, TArray<UProjectileEffect*> ProjectileEffects)
{
	Characteristics = ProjectileCharacteristics;

	Characteristics.Damages *= WeaponCharacteristics.DamagesMultiplier;
	Characteristics.Range *= WeaponCharacteristics.RangeMultiplier;
	Characteristics.Size *= WeaponCharacteristics.ProjectileSizeMultiplier;
	Characteristics.Speed *= WeaponCharacteristics.ProjectileSpeedMultiplier;
	Characteristics.CriticalHitChance *= WeaponCharacteristics.CriticalHitChanceMultiplier;

	SetActorScale3D(FVector(Characteristics.Size));

	Effects = ProjectileEffects;

	for (auto effect : Effects)
	{
		if (!effect->IsA(UProjectileTransformEffect::StaticClass()) || !bHasTransformEffect)
		{
			effect->RegisterProjectile(this);

			if (!bHasTransformEffect)
				bHasTransformEffect = true;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// --- BEHAVIOUR
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveProjectile(DeltaTime);
}

void AProjectile::MoveProjectile(float DeltaTime)
{
	const FVector originLocation = GetActorLocation();
	const FVector movement = Direction * Characteristics.Speed * DeltaTime;

	ElapsedRange += movement.Length();

	if (ElapsedRange >= Characteristics.Range)
	{
		DestroyProjectile();

		return;
	}

	AddActorWorldOffset(movement, false);

	CheckForCollisionsAfterMovement(originLocation);
}

void AProjectile::CheckForCollisionsAfterMovement(const FVector OriginLocation)
{
	TArray<FHitResult> outHits;
	const FCollisionShape shape = FCollisionShape::MakeSphere(Collision->GetScaledSphereRadius());
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	GetWorld()->SweepMultiByChannel(outHits, OriginLocation, GetActorLocation(), FQuat::Identity, ECollisionChannel::ECC_Visibility, shape, params);

	for (auto outHit : outHits)
	{
		if (IsValid(LastActorHit))
		{
			if (LastActorHit == outHit.GetActor()) continue;
		}

		HitSomething(outHit.GetActor(), outHit.Location, OriginLocation);

		if (!bCanPierce) break;
	}
}

void AProjectile::HitSomething(AActor* OtherActor, FVector HitLocation, FVector OriginLocation)
{
	LastActorHit = OtherActor;

	UProjectileInteraction* projectileInteraction = OtherActor->FindComponentByClass<UProjectileInteraction>();

	if (IsValid(projectileInteraction))
	{
		projectileInteraction->HitByProjectile(this);
	}

	OnProjectileHitDelegate.Broadcast(this, HitLocation, OriginLocation);

	if (!bHasTransformEffect) {
		Destroy();
		return;
	}

	for (const auto effect : Effects)
	{
		if (effect->IsA(UProjectileTransformEffect::StaticClass()))
		{
			effect->RegisterProjectile(this);
			bHasTransformEffect = true;
			break;
		}
	}
}

void AProjectile::SetRandomDirection()
{
	FVector newDirection = FVector::ForwardVector;

	newDirection = newDirection.RotateAngleAxis(FMath::FRandRange(0.0f, 360.0f), FVector::UpVector);

	Direction = newDirection;
}

void AProjectile::DestroyProjectile()
{
	Destroy();
}

float AProjectile::GetDamages()
{
	const bool bIsCritical = FMath::FRand() <= Characteristics.CriticalHitChance;

	const float output = bIsCritical ? Characteristics.Damages * Characteristics.CriticalHitMultiplier : Characteristics.Damages;

	return output;
}

FProjectileCharacteristics* AProjectile::GetCharacteristics()
{
	return &Characteristics;
}

void AProjectile::RemoveTransformEffect(UProjectileTransformEffect* Effect)
{
	Effects.Remove(Effect);
}