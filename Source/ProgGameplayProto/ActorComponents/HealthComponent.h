// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileInteraction.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthDie);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthParamChanged, float, NewParamValue);

/**
 *
 */
UCLASS()
class PROGGAMEPLAYPROTO_API UHealthComponent : public UProjectileInteraction
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

public:
	UPROPERTY()
	FOnHealthDie OnBeforeHealthDie;

	UPROPERTY()
	FOnHealthDie OnHealthDie;

	UPROPERTY(BlueprintAssignable)
	FOnHealthParamChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnHealthParamChanged OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnHealthParamChanged OnRegenerationRateChanged;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void InitializeHealth(float NewMaxHealth = 10, float NewRegenerationRate = 0);

	virtual void TryRegenerate(float DeltaTime);

	virtual void HitByProjectile(AProjectile* Projectile) override;

	virtual void AddHealth(float Amount);

	virtual void RestoreFullHealth();

	virtual void Die();

	virtual void SetMaxHealth(float NewMaxHealth);

	virtual void SetRegenerationRate(float NewRegenerationRate);
};
