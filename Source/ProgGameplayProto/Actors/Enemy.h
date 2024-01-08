// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "ProgGameplayProto/DataAssets/PersonaCharacteristics.h"
#include "ProgGameplayProto/DataAssets/Enemies/EnemyCharacteristics.h"
#include "Enemy.generated.h"

class UProjectileData;
class UWeaponData;
class UWeaponComponent;
class UHealthComponent;
class UEnemyDropperComponent;
class UCapsuleComponent;
class UEnemyData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEnemyDie, AEnemy*, Enemy, bool, bIsGettingPoints);

UCLASS()
class PROGGAMEPLAYPROTO_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	FOnEnemyDie DieDelegate;

	float DistanceFromPlayerSqrd;

	// Sets default values for this pawn's properties
	AEnemy();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	UCapsuleComponent* Collision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	UEnemyDropperComponent* Dropper;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	UHealthComponent* Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	UWeaponComponent* Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	UEnemyData* EnemyData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	UWeaponData* WeaponData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	UProjectileData* ProjectileData;

	FPersonaCharacteristics PersonaCharacteristics;

	FEnemyCharacteristics EnemyCharacteristics;

	FVector Location;
	FVector MovingDirection;
	float MovingSpeed;

	FRotator Rotation;
	FRotator RotationTarget;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	virtual void SetupComponents();

	void InitializeEnemyVariables();

	void Move(float DeltaTime);

	void Rotate(float DeltaTime, const FVector& PlayerPosition);

	void RunnerBehave(const float DeltaTime);

	void AggressiveBehave(const float DeltaTime);

	virtual void Behave(const float DeltaTime, const FVector& PlayerPosition);

	UFUNCTION(BlueprintImplementableEvent)
	void OnHit(const FRotator& ProjectileRotation, const float ProjectileSpeed);

	UFUNCTION(BlueprintCallable)
	virtual void Die();

	// --- GETTERS
	FORCEINLINE UWeaponComponent* GetWeapon() const { return Weapon; }

	FORCEINLINE UEnemyData* GetEnemyData() const { return EnemyData; }

	FORCEINLINE UWeaponData* GetWeaponData() const { return WeaponData; }

	FORCEINLINE UProjectileData* GetProjectileData() const { return ProjectileData; }

	FORCEINLINE FEnemyCharacteristics GetEnemyCharacteristics() const { return EnemyCharacteristics; }

	FORCEINLINE FPersonaCharacteristics GetPersonaCharacteristics() const { return PersonaCharacteristics; }
};