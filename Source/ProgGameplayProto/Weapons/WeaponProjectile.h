// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponProjectile.generated.h"

class UProjectileEffect;
class USphereComponent;
class UStaticMeshComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FProjectileHitDelegate, AWeaponProjectile*, Projectile, FVector, HitLocation, FVector, OriginLocation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FProjectileDestroyDelegate, AWeaponProjectile*, Projectile);

UCLASS()
class PROGGAMEPLAYPROTO_API AWeaponProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeaponProjectile();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* Collision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY()
	AActor* LastActorHit;

	FVector Direction;

	float Size;
	float Range;
	float Speed;
	float BaseDamages;
	float CriticalHitChance;
	float CriticalHitMultiplier;

	bool bCanPierce;

	float ElapsedRange;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable)
	FProjectileHitDelegate OnProjectileHit;

	UPROPERTY(BlueprintAssignable)
	FProjectileDestroyDelegate OnProjectileDestroy;

	UPROPERTY()
	TArray<UProjectileEffect*> Effects;

	int32 NumberOfHitsBeforeDestroy = 1;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetParameters(float NewSize, float NewRange, float NewSpeed, float NewBaseDamages, float NewCriticalHitChance, float NewCriticalHitMultiplier);

	virtual void MoveProjectile(float DeltaTime);

	virtual void CheckForCollisionsAfterMovement(FVector OriginLocation);

	virtual void HitSomething(AActor* OtherActor, FVector HitLocation, FVector OriginLocation);

	virtual void SetRandomDirection();

	virtual void DestroyProjectile();

	virtual float GetDamages();

public:
	FORCEINLINE virtual void SetDirection(FVector NewDirection) { Direction = NewDirection; }
};
