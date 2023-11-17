// Fill out your copyright notice in the Description page of Project Settings.


#include "Health.h"

#include "Weapons/WeaponProjectile.h"


void UHealth::BeginPlay()
{
	Super::BeginPlay();

	PrimaryComponentTick.bCanEverTick = false;
}

// Called every frame
void UHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TryRegenerate(DeltaTime);
}

void UHealth::InitializeHealth(float NewMaxHealth, float NewRegenerationRate)
{
	SetMaxHealth(NewMaxHealth);

	CurrentHealth = MaxHealth;

	SetRegenerationRate(NewRegenerationRate);
}

void UHealth::TryRegenerate(float DeltaTime)
{
	TimeElapsedSinceLastRegeneration += DeltaTime;

	if (TimeElapsedSinceLastRegeneration >= 1)
	{
		TimeElapsedSinceLastRegeneration = 0;

		AddHealth(RegenerationRate);
	}
}

void UHealth::HitByProjectile(AWeaponProjectile* Projectile)
{
	Super::HitByProjectile(Projectile);

	const float damages = Projectile->GetDamages();

	AddHealth(-damages);
}

void UHealth::HitByAttack(float Damages, AActor* Attacker)
{
	AddHealth(-Damages);
}

void UHealth::AddHealth(float Amount)
{
	if (CurrentHealth == MaxHealth && Amount >= 0) return;

	CurrentHealth = FMath::Clamp(CurrentHealth + Amount, 0, MaxHealth);
	OnHealthChanged.Broadcast(CurrentHealth);

	if (CurrentHealth == 0) Die();
}

void UHealth::SetMaxHealth(float NewMaxHealth)
{
	MaxHealth = NewMaxHealth;
}

void UHealth::SetRegenerationRate(float NewRegenerationRate)
{
	RegenerationRate = NewRegenerationRate;

	PrimaryComponentTick.bCanEverTick = (RegenerationRate > 0);
}

void UHealth::Die()
{
	OnBeforeHealthDie.Broadcast();

	OnHealthDie.Broadcast();
}

float UHealth::GetCurrentHealthPercentage()
{
	float output = CurrentHealth / MaxHealth;

	output = FMath::Clamp(output, 0, 1);

	return output;
}
