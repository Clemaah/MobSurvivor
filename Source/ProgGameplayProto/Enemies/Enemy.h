// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "EnemyData.h"
#include "ProgGameplayProto/Characters/PersonaCharacteristics.h"
#include "Enemy.generated.h"


struct FPersonaCharacteristics;
struct FWeaponCharacteristics;
class UProjectileEffect;
struct FProjectileCharacteristics;
class AProjectile;
class UEnemyDropperComponent;
class UCapsuleComponent;
class UHealthComponent;
class UWeaponComponent;
class UEnemyData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyDie, AEnemy*, Enemy);

UCLASS()
class PROGGAMEPLAYPROTO_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	FOnEnemyDie DieDelegate;

	// Sets default values for this pawn's properties
	AEnemy();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	UEnemyData* EnemyData;

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
	FPersonaCharacteristics PersonaCharacteristics;

	FVector Direction;

	float Speed;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	virtual void Move(float DeltaTime, FVector PlayerPosition);

	UFUNCTION(BlueprintCallable)
	virtual void Die();

	UFUNCTION(BlueprintCallable)
	virtual void SetupComponents();

	void InitializeEnnemyVariables();

	void ChangeDirection(FVector Target);

	// --- GETTERS
	FORCEINLINE UWeaponComponent* GetWeapon() const { return Weapon; }

	FORCEINLINE UEnemyData* GetEnemyData() const { return EnemyData; }

	FORCEINLINE FPersonaCharacteristics GetCharacteristics() const { return PersonaCharacteristics; }
};