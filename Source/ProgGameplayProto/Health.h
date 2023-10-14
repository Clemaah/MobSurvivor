// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileInteraction.h"
#include "Health.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthDie);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, NewHealthValue);

/**
 *
 */
UCLASS()
class PROGGAMEPLAYPROTO_API UHealth : public UProjectileInteraction
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth = 10;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	float CurrentHealth;

	virtual void BeginPlay() override;

public:
	UPROPERTY()
	FOnHealthDie OnBeforeHealthDie;

	UPROPERTY()
	FOnHealthDie OnHealthDie;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

public:
	virtual void HitByProjectile(AWeaponProjectile* Projectile) override;
	virtual void HitByAttack(float Damages, AActor* Attacker);
	virtual void AddHealth(float Amount);
	virtual void Die();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetCurrentHealth() { return CurrentHealth; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual float GetCurrentHealthPercentage();
};
