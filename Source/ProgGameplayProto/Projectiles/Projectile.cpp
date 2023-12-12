// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ProgGameplayProto/ProjectileInteraction.h"
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

void AProjectile::InitializeProjectile(const FProjectileCharacteristics& ProjectileCharacteristics, const FWeaponCharacteristics& WeaponCharacteristics)
{
	Characteristics = ProjectileCharacteristics;

	Characteristics.Damages *= WeaponCharacteristics.DamagesMultiplier;
	Characteristics.Range *= WeaponCharacteristics.RangeMultiplier;
	Characteristics.Size *= WeaponCharacteristics.ProjectileSizeMultiplier;
	Characteristics.Speed *= WeaponCharacteristics.ProjectileSpeedMultiplier;
	Characteristics.CriticalHitChance *= WeaponCharacteristics.CriticalHitChanceMultiplier;

	SetActorScale3D(FVector(Characteristics.Size));
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

	for (int i = 0; i < outHits.Num(); i++)
	{
		if (IsValid(LastActorHit))
		{
			if (LastActorHit == outHits[i].GetActor()) continue;
		}

		HitSomething(outHits[i].GetActor(), outHits[i].Location, OriginLocation);

		OnProjectileHitDelegate.Broadcast(this, outHits[i].Location, OriginLocation);

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


	Characteristics.NumberOfBouncesBeforeDestroy -= 1;
	Characteristics.NumberOfPierceBeforeDestroy -= 1;

	if (Characteristics.NumberOfBouncesBeforeDestroy < 1)
		DestroyProjectile();

	if (Characteristics.NumberOfPierceBeforeDestroy < 1)
		DestroyProjectile();


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