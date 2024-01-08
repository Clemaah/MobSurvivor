// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "ProgGameplayProto/DataAssets/Projectiles/ProjectileCharacteristics.h"
#include "ProgGameplayProto/DataAssets/Weapons/WeaponCharacteristics.h"

#include "WeaponComponent.generated.h"

struct FPersonaCharacteristics;
struct FWeaponCharacteristics;
struct FProjectileCharacteristics;

class AProjectile;
class UProjectileEffect;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROGGAMEPLAYPROTO_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

	/* ---------------------- VARIABLES ----------------------*/

protected:
	// --- CHARACTER REFERENCE
	TObjectPtr<APawn> Pawn;


	// --- OTHER VARIABLES
	FPersonaCharacteristics* PersonaCharacteristics;

	FWeaponCharacteristics WeaponCharacteristics;

	FProjectileCharacteristics ProjectileCharacteristics;

	TSubclassOf<AProjectile> WeaponProjectileToSpawn;

	TArray<TSubclassOf<UProjectileEffect>> Effects;

	float TimeElapsedSinceLastShoot = 0;

	bool bHasAlreadyDoubleShot;

public:
	bool bCanShoot;



	/* ---------------------- FUNCTIONS ----------------------*/

	// --- INITIALIZATION
public:
	UWeaponComponent();

	virtual void InitializeWeapon(
		APawn* InPawn, 
		FPersonaCharacteristics* InPersonaCharacteristics, 
		const FWeaponCharacteristics InWeaponCharacteristics, 
		const FProjectileCharacteristics InProjectileCharacteristics, 
		const TSubclassOf<AProjectile> InProjectileToSpawn, 
		const TArray<TSubclassOf<UProjectileEffect>> ProjectileEffects);

	// --- BEHAVIOUR
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Shoot(FRotator Rotation);

protected:

	void Reload(float DeltaTime);
	void TryDoubleShoot();

	virtual void SpawnProjectile(FVector Direction);

	virtual TArray<FVector> ComputeSpreadDirections(FRotator Rotation);

	virtual bool ActivateDoubleShot();



	// --- GETTERS
	virtual float GetShootDelay();

	virtual float GetPrecisionRandomAngle();

	virtual float GetSpread();


	// --- SETTERS
public:
	virtual void UpdateCharacteristics(FWeaponCharacteristics& WeaponBonuses, FProjectileCharacteristics& ProjectileBonuses);

	virtual void AddEffect(TSubclassOf<UProjectileEffect> Effect);
};
