// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "GameFramework/Character.h"
#include "ProgGameplayProto/DataAssets/PersonaCharacteristics.h"
#include "ProgGameplayProto/DataAssets/Characters/CharacterCharacteristics.h"
#include "MobSurvivorCharacter.generated.h"


class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

class UCameraComponent;
class USpringArmComponent;
class UWeaponComponent;
class UExperienceComponent;
class UHealthComponent;
class USphereComponent;

struct FPersonaCharacteristics;
struct FProjectileCharacteristics;
struct FWeaponCharacteristics;

class UProjectileEffect;

DECLARE_LOG_CATEGORY_EXTERN(LogCharacter, Log, All);


UCLASS(config = Game, Meta = (PrioritizeCategories = "Custom"))
class AMobSurvivorCharacter : public ACharacter
{
	GENERATED_BODY()

	/* ---------------------- VARIABLES ----------------------*/

public:
	// --- STATICS
	static AMobSurvivorCharacter* Instance;


private:
	// ----- CAMERA
	// Camera boom positioning the camera behind the character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	// Follow camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;


	// ----- ACTIONS
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom|Inputs", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom|Inputs", meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom|Inputs", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom|Inputs", meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom|Inputs", meta = (AllowPrivateAccess = "true"))
	UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom|Inputs", meta = (AllowPrivateAccess = "true"))
	UInputAction* AutoFireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom|Inputs", meta = (AllowPrivateAccess = "true"))
	UInputAction* PauseAction;

protected:
	// --- COMPONENTS
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom|Components")
	USphereComponent* DropsCollector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom|Components")
	UStaticMeshComponent* DropsCollectorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom|Components")
	UHealthComponent* Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom|Components")
	UExperienceComponent* Experience;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom|Components")
	UWeaponComponent* Weapon;


	// --- OTHER VARIABLES
	FPersonaCharacteristics PersonaCharacteristics;

	FCharacterCharacteristics CharacterCharacteristics;

	bool bIsHoldingShoot = false;
	bool bIsAutoFire = false;
	bool bWantsToShoot = false;



	/* ---------------------- FUNCTIONS ----------------------*/

	// --- INITIALIZATION
	virtual void BeginPlay() override;

public:
	AMobSurvivorCharacter();

	virtual void RegisterInstance();

	UFUNCTION(BlueprintCallable)
	virtual void SetupComponents(
		const FPersonaCharacteristics InPersonaCharacteristics, 
		const FCharacterCharacteristics InCharacterCharacteristics, 
		const FWeaponCharacteristics InWeaponCharacteristics, 
		const FProjectileCharacteristics InProjectileCharacteristics, 
		const TSubclassOf<AProjectile> InProjectileToSpawn,
		const TArray<TSubclassOf<UProjectileEffect>> ProjectileEffects);

	virtual void InitializeCharacterVariables();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// --- ACTIONS
	virtual void Tick(float DeltaSeconds) override;

	void Move(const FInputActionValue& Value);

	void Shoot(const FInputActionValue& Value);

	void StopShoot(const FInputActionValue& Value);

	void AutoFire(const FInputActionValue& Value);

	FVector GetMouseDirection();

	virtual void WantsToShoot();


	// --- EVENTS
	UFUNCTION()
	virtual void OnDropsCollectorBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	// --- GETTERS
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE UExperienceComponent* GetExperience() const { return Experience; }

	FORCEINLINE UHealthComponent* GetHealth() const { return Health; }

	FORCEINLINE UWeaponComponent* GetWeapon() const { return Weapon; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE FCharacterCharacteristics GetCharacterCharacteristics() const { return CharacterCharacteristics; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE FPersonaCharacteristics GetPersonaCharacteristics() const { return PersonaCharacteristics; }



	// --- SETTERS
	UFUNCTION()
	virtual void UpdateCharacteristics(FPersonaCharacteristics& PersonaBonuses, FCharacterCharacteristics& CharacterBonuses);
};

