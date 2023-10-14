// Fill out your copyright notice in the Description page of Project Settings.


#include "Health.h"

#include "Weapons/WeaponProjectile.h"

void UHealth::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
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
	CurrentHealth += Amount;

	OnHealthChanged.Broadcast(CurrentHealth);

	if (CurrentHealth <= 0)
		Die();
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
