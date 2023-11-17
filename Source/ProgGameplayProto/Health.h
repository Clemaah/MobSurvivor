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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RegenerationRate = 0;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	float CurrentHealth = 10;

	float TimeElapsedSinceLastRegeneration = 0;

	virtual void BeginPlay() override;

public:
	UPROPERTY()
	FOnHealthDie OnBeforeHealthDie;

	UPROPERTY()
	FOnHealthDie OnHealthDie;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void InitializeHealth(float maxHealth = 10, float RegenerationRate = 0);

	virtual void TryRegenerate(float DeltaTime);

	virtual void HitByProjectile(AWeaponProjectile* Projectile) override;

	virtual void HitByAttack(float Damages, AActor* Attacker);

	virtual void AddHealth(float Amount);

	virtual void SetMaxHealth(float NewMaxHealth);

	virtual void SetRegenerationRate(float NewRegenerationRate);

	virtual void Die();

	virtual float GetMaxHealth() { return MaxHealth; }
	virtual float GetRegenerationRate() { return RegenerationRate; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetCurrentHealth() { return CurrentHealth; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual float GetCurrentHealthPercentage();
};
