// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "EnemyCharacteristics.h"
#include "EnemyData.h"
#include "Enemy.generated.h"


class UEnemyDropperComponent;
class UCapsuleComponent;
class UHealthComponent;
class UWeaponComponent;
class UEnemyData;

UCLASS()
class PROGGAMEPLAYPROTO_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* Collision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UHealthComponent* Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UEnemyDropperComponent* Dropper;

	UPROPERTY(Category = "EnemyParameters", EditAnywhere, BlueprintReadWrite)
	float MoveSpeed;

	UPROPERTY(Category = "EnemyParameters", EditAnywhere, BlueprintReadWrite)
	float Damages;

	UPROPERTY(Category = "EnemyParameters", EditAnywhere, BlueprintReadWrite)
	int Points;

	UPROPERTY(Category = "EnemyParameters", EditAnywhere, BlueprintReadWrite)
	UEnemyData* EnemyData;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom|Enemy")
	FEnemyCharacteristics EnemyCharacteristics;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom|Components")
	UWeaponComponent* Weapon;

	

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void MoveTowardPlayer(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	virtual void Die();


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	virtual void TryAttacking(AActor* Target);
	UFUNCTION(BlueprintCallable)
	virtual void SetupComponents(/*const FCharacterCharacteristics InCharacterCharacteristics,*/ const FWeaponCharacteristics InWeaponCharacteristics, const FProjectileCharacteristics InProjectileCharacteristics);

	UFUNCTION(BlueprintImplementableEvent)
	void Attack_BP(AActor* Target);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom|Projectile")
	TSubclassOf<AProjectile> WeaponProjectileToSpawn;

	// --- GETTERS
	FORCEINLINE UWeaponComponent* GetWeapon() const { return Weapon; }

	FORCEINLINE FEnemyCharacteristics GetCharacteristics() const { return EnemyCharacteristics; }

	//FORCEINLINE UEnemyData GetEnemyData() const { return EnemyData; }

	// --- SETTERS
	//UFUNCTION()
	//virtual void UpdateCharacteristics(FEnemyCharacteristics& Other);

};