// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProgGameplayProto/Projectiles/ProjectileCharacteristics.h"
#include "WeaponCharacteristics.h"
#include "ProgGameplayProto/Characters/PersonaCharacteristics.h"
#include "WeaponComponent.generated.h"

struct FMobSurvivorParameters;
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
	TObjectPtr<APawn> Pawn;


	// --- OTHER VARIABLES
	FPersonaCharacteristics* PersonaCharacteristics;

	FWeaponCharacteristics WeaponCharacteristics;

	FProjectileCharacteristics ProjectileCharacteristics;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UProjectileEffect>> Effects;

	float TimeElapsedSinceLastShoot = 0;

	bool bIsDoubleShotActivated;

public:
	bool bWantsToShoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom|Projectile")
	TSubclassOf<AProjectile> WeaponProjectileToSpawn;



	/* ---------------------- FUNCTIONS ----------------------*/

	// --- INITIALIZATION
public:
	UWeaponComponent();

	virtual void InitializeWeapon(APawn* InPawn, FPersonaCharacteristics* InPersonaCharacteristics, const FWeaponCharacteristics InWeaponCharacteristics, const
	                              FProjectileCharacteristics InProjectileCharacteristics, const TArray<TSubclassOf<UProjectileEffect>> ProjectileEffects);

	// --- BEHAVIOUR
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void TryShooting(float DeltaTime);

	virtual void SpawnProjectile(FVector Direction);

protected:
	virtual void Shoot();

	virtual TArray<FVector> ComputeSpreadDirections();

	virtual bool CanActivateDoubleShot();



	// --- GETTERS
	virtual FVector GetMouseDirection();

	FVector GetPlayerDirection();

	virtual float GetShootDelay();

	virtual float GetPrecisionRandomAngle();

	virtual float GetSpread();


	// --- SETTERS
public:
	virtual void UpdateCharacteristics(FWeaponCharacteristics& WeaponBonuses, FProjectileCharacteristics& ProjectileBonuses);

	virtual void AddEffect(TSubclassOf<UProjectileEffect> Effect);
};
