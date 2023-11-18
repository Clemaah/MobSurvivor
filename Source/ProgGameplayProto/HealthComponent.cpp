// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "Weapons/WeaponProjectile.h"


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (RegenerationRate > 0)
		TryRegenerate(DeltaTime);
}

void UHealthComponent::InitializeHealth(float NewMaxHealth, float NewRegenerationRate)
{
	SetMaxHealth(NewMaxHealth);

	CurrentHealth = MaxHealth;

	SetRegenerationRate(NewRegenerationRate);
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

void UHealthComponent::HitByProjectile(AWeaponProjectile* Projectile)
{
	Super::HitByProjectile(Projectile);

	const float damages = Projectile->GetDamages();

	AddHealth(-damages);
}

void UHealthComponent::HitByAttack(float Damages, AActor* Attacker)
{
	AddHealth(-Damages);
}

void UHealthComponent::AddHealth(float Amount)
{
	if (CurrentHealth == MaxHealth && Amount >= 0) return;

	CurrentHealth = FMath::Clamp(CurrentHealth + Amount, 0, MaxHealth);
	OnHealthChanged.Broadcast(CurrentHealth);

	if (CurrentHealth == 0) Die();
}

void UHealthComponent::Die()
{
	OnBeforeHealthDie.Broadcast();

	OnHealthDie.Broadcast();
}

float UHealthComponent::GetCurrentHealthPercentage()
{
	float output = CurrentHealth / MaxHealth;

	output = FMath::Clamp(output, 0, 1);

	return output;
}
