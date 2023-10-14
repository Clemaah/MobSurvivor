// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponProjectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ProgGameplayProto/ProjectileInteraction.h"

// Sets default values
AWeaponProjectile::AWeaponProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>("Collision");
	SetRootComponent(Collision);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Collision);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AWeaponProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWeaponProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveProjectile(DeltaTime);
}

void AWeaponProjectile::SetParameters(float NewSize, float NewRange, float NewSpeed, float NewBaseDamages, float NewCriticalHitChance, float NewCriticalHitMultiplier)
{
	Size = NewSize;
	Range = NewRange;
	Speed = NewSpeed;
	BaseDamages = NewBaseDamages;
	CriticalHitChance = NewCriticalHitChance;
	CriticalHitMultiplier = NewCriticalHitMultiplier;
}

void AWeaponProjectile::MoveProjectile(float DeltaTime)
{
	const FVector originLocation = GetActorLocation();
	const FVector movement = Direction * Speed * DeltaTime;

	ElapsedRange += movement.Length();

	if (ElapsedRange >= Range)
	{
		DestroyProjectile();

		return;
	}

	AddActorWorldOffset(movement, false);

	CheckForCollisionsAfterMovement(originLocation);
}

void AWeaponProjectile::CheckForCollisionsAfterMovement(const FVector OriginLocation)
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

		OnProjectileHit.Broadcast(this, outHits[i].Location, OriginLocation);

		if (!bCanPierce) break;
	}
}

void AWeaponProjectile::HitSomething(AActor* OtherActor, FVector HitLocation, FVector OriginLocation)
{
	LastActorHit = OtherActor;

	UProjectileInteraction* projectileInteraction = OtherActor->FindComponentByClass<UProjectileInteraction>();

	if (IsValid(projectileInteraction))
	{
		projectileInteraction->HitByProjectile(this);
	}

	OnProjectileHit.Broadcast(this, HitLocation, OriginLocation);

	NumberOfHitsBeforeDestroy -= 1;

	if (NumberOfHitsBeforeDestroy < 1)
		DestroyProjectile();
}

void AWeaponProjectile::SetRandomDirection()
{
	FVector newDirection = FVector::ForwardVector;

	newDirection = newDirection.RotateAngleAxis(FMath::FRandRange(0.0f, 360.0f), FVector::UpVector);

	Direction = newDirection;
}

void AWeaponProjectile::DestroyProjectile()
{
	Destroy();
}

float AWeaponProjectile::GetDamages()
{
	const bool bIsCritical = FMath::FRand() <= CriticalHitChance;

	const float output = bIsCritical ? BaseDamages * CriticalHitMultiplier : BaseDamages;

	return output;
}