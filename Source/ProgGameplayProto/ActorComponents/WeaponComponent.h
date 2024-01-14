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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReloadSignature, bool, IsReloading);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAmmoChangedSignature, int, numberOfAmmo);


UENUM()
enum EWeaponState
{
	Armed, Reloading, Firing
};

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

	float ShootElapsedTime = 0;

	float ReloadElapsedTime = 0;

	int RemainingAmmunition = 0;

	bool bHasAlreadyDoubleShot;

	EWeaponState State;

public:
	UPROPERTY(BlueprintAssignable)
	FOnReloadSignature OnReloadDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnAmmoChangedSignature OnShootDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnAmmoChangedSignature OnTotalAmmoChangedSignature;



	/* ---------------------- FUNCTIONS ----------------------*/

	// --- INITIALIZATION
public:
	UWeaponComponent();

	void InitializeWeapon(
		APawn* InPawn, 
		FPersonaCharacteristics* InPersonaCharacteristics, 
		const FWeaponCharacteristics& InWeaponCharacteristics, 
		const FProjectileCharacteristics& InProjectileCharacteristics, 
		const TSubclassOf<AProjectile> InProjectileToSpawn, 
		const TArray<TSubclassOf<UProjectileEffect>>& ProjectileEffects);

	// --- BEHAVIOUR
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	void TryShooting(const FRotator& Rotation);

protected:
	void Shoot(const FRotator& Rotation);

	void Reload(float DeltaTime);

	void TryRearming(float ElapsedTime, float& Timer, float TimerDuration);

	bool TryDoubleShoot() const;

	void SpawnProjectile(FVector Direction) const;

	TArray<FVector> ComputeSpreadDirections(const FRotator& Rotation);



	// --- GETTERS
	virtual float GetShootDelay();

	virtual float GetPrecisionRandomAngle();

	virtual float GetSpread();

	UFUNCTION(BlueprintPure)
	virtual float GetReloadingTimePercentage();


	// --- SETTERS
public:
	virtual void UpdateCharacteristics(FWeaponCharacteristics& WeaponBonuses, FProjectileCharacteristics& ProjectileBonuses);

	virtual void AddEffect(TSubclassOf<UProjectileEffect> Effect);
};
