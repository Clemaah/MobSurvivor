// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileCharacteristics.h"
#include "Projectile.generated.h"

struct FWeaponCharacteristics;
class UProjectileEffect;
class USphereComponent;
class UStaticMeshComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FProjectileHitSignature, AProjectile*, Projectile, FVector, HitLocation, FVector, OriginLocation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FProjectileDestroySignature, AProjectile*, Projectile);

UCLASS()
class PROGGAMEPLAYPROTO_API AProjectile : public AActor
{
	GENERATED_BODY()

	/* ---------------------- VARIABLES ----------------------*/

protected:
	// --- COMPONENTS
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* Collision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;


	// --- OTHER VARIABLES
	UPROPERTY()
	FProjectileCharacteristics Characteristics;

	UPROPERTY()
	TArray<UProjectileEffect*> Effects;

	UPROPERTY()
	AActor* LastActorHit;

	FVector Direction;

	float ElapsedRange;

	bool bCanPierce;


	// --- DELEGATES
public:
	UPROPERTY(BlueprintAssignable)
	FProjectileHitSignature OnProjectileHitDelegate;

	UPROPERTY(BlueprintAssignable)
	FProjectileDestroySignature OnProjectileDestroyDelegate;



	/* ---------------------- FUNCTIONS ----------------------*/

	// --- INITIALIZATION
	AProjectile();

	virtual void InitializeProjectile(const FProjectileCharacteristics& ProjectileCharacteristics, const FWeaponCharacteristics& WeaponCharacteristics);


	// --- BEHAVIOUR
	virtual void Tick(float DeltaTime) override;
	
	virtual void MoveProjectile(float DeltaTime);

	virtual void CheckForCollisionsAfterMovement(FVector OriginLocation);

	virtual void HitSomething(AActor* OtherActor, FVector HitLocation, FVector OriginLocation);

	virtual void DestroyProjectile();


	// --- GETTERS
	virtual float GetDamages();
	virtual FProjectileCharacteristics* GetCharacteristics();


	// --- SETTERS
	FORCEINLINE virtual void SetDirection(FVector NewDirection) { Direction = NewDirection; }

	virtual void SetRandomDirection();
};
