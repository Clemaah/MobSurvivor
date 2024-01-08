// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "ProgGameplayProto/Actors/Projectile.h"


void UHealthComponent::InitializeHealth(float NewMaxHealth, float NewRegenerationRate)
{
	SetMaxHealth(NewMaxHealth);
	SetRegenerationRate(NewRegenerationRate);
	RestoreFullHealth();
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (RegenerationRate > 0)
		TryRegenerate(DeltaTime);
}

void UHealthComponent::TryRegenerate(float DeltaTime)
{
	TimeElapsedSinceLastRegeneration += DeltaTime;

	if (TimeElapsedSinceLastRegeneration >= 1)
	{
		TimeElapsedSinceLastRegeneration = 0;

		AddHealth(RegenerationRate);
	}
}

void UHealthComponent::HitByProjectile(AProjectile* Projectile)
{
	Super::HitByProjectile(Projectile);

	const float damages = Projectile->GetDamages();

	AddHealth(-damages);
}

void UHealthComponent::AddHealth(float Amount)
{
	if (CurrentHealth == 0 || CurrentHealth == MaxHealth && Amount >= 0) return;

	CurrentHealth = FMath::Clamp(CurrentHealth + Amount, 0, MaxHealth);
	OnHealthChanged.Broadcast(CurrentHealth);

	if (CurrentHealth == 0) Die();
}

void UHealthComponent::RestoreFullHealth()
{
	CurrentHealth = MaxHealth;
	OnHealthChanged.Broadcast(CurrentHealth);
}

void UHealthComponent::Die()
{
	OnBeforeHealthDie.Broadcast();

	OnHealthDie.Broadcast();
}


void UHealthComponent::SetMaxHealth(float NewMaxHealth)
{
	MaxHealth = NewMaxHealth;
	OnMaxHealthChanged.Broadcast(MaxHealth);
}

void UHealthComponent::SetRegenerationRate(float NewRegenerationRate)
{
	RegenerationRate = NewRegenerationRate;
	OnRegenerationRateChanged.Broadcast(RegenerationRate);
}
