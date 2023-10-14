// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Enemy.generated.h"

class UEnemyDropperComponent;
class UCapsuleComponent;
class UHealth;

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
	UHealth* Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UEnemyDropperComponent* Dropper;

	UPROPERTY(Category = EnemyParameters, EditAnywhere, BlueprintReadWrite)
	float MoveSpeed;

	UPROPERTY(Category = EnemyParameters, EditAnywhere, BlueprintReadWrite)
	float Damages;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void MoveTowardPlayer(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	virtual void Die();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	virtual void TryAttacking(AActor* Target);

	UFUNCTION(BlueprintImplementableEvent)
	void Attack_BP(AActor* Target);
};