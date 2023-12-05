// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProgGameplayProto/Projectiles/ProjectileCharacteristics.h"
#include "WeaponCharacteristics.h"
#include "WeaponComponent.generated.h"

class UProjectileData;
class AProjectile;
class UProjectileEffect;
class UWeaponData;
class AProgGameplayProtoCharacter;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROGGAMEPLAYPROTO_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

	/* ---------------------- VARIABLES ----------------------*/

protected:
	// --- CHARACTER REFERENCE
	TObjectPtr<AProgGameplayProtoCharacter> Character;


	// --- OTHER VARIABLES
	FWeaponCharacteristics WeaponCharacteristics;

	FProjectileCharacteristics ProjectileCharacteristics;

	TArray<UProjectileEffect*> Effects;

	float TimeElapsedSinceLastShoot = 0;

	bool isDoubleShotActivated;



	/* ---------------------- FUNCTIONS ----------------------*/

	// --- INITIALIZATION
public:
	UWeaponComponent();

	virtual void InitializeWeapon(AProgGameplayProtoCharacter* NewCharacter, UWeaponData* Weapon, int WeaponLevel, UProjectileData* Projectile, int ProjectileLevel);


	// --- BEHAVIOUR
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void TryShooting(float DeltaTime);

protected:
	virtual void Shoot();

	virtual TArray<FVector> ComputeSpreadDirections();

	virtual bool CanActivateDoubleShot();

	virtual void SpawnProjectile(FVector Direction);


	// --- GETTERS
	virtual FVector GetMouseDirection();

	virtual float GetShootDelay();

	virtual float GetPrecisionRandomAngle();

	virtual float GetSpread();


	// --- SETTERS
public:
	virtual void UpdateCharacteristics(FWeaponCharacteristics& WeaponBonuses, FProjectileCharacteristics& ProjectileBonuses);

	virtual void AddEffect(UProjectileEffect* Effect);
};
