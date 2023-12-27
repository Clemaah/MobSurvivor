// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "CharacterCharacteristics.h"
#include "ProgGameplayProtoCharacter.generated.h"


class UProjectileEffect;
struct FProjectileCharacteristics;
struct FWeaponCharacteristics;
class UProjectileData;
struct FInputActionValue;
struct FMobSurvivorParameters;

class UCameraComponent;
class USpringArmComponent;
class USphereComponent;
class UHealthComponent;
class UExperienceComponent;
class UWeaponComponent;

class UInputMappingContext;
class UInputAction;

class UBonusData;
class UCharacterData;
class UWeaponData;

class AProjectile;



DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);


UCLASS(config = Game, Meta = (PrioritizeCategories = "Custom"))
class AProgGameplayProtoCharacter : public ACharacter
{
	GENERATED_BODY()

	/* ---------------------- VARIABLES ----------------------*/

public:
	// --- STATICS
	static AProgGameplayProtoCharacter* Instance;


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

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom|Character")
	FCharacterCharacteristics CharacterCharacteristics;

	bool bIsHoldingShoot = false;

	bool bIsAutoFire = false;



	/* ---------------------- FUNCTIONS ----------------------*/

	// --- INITIALIZATION
	virtual void BeginPlay() override;

public:
	AProgGameplayProtoCharacter();

	virtual void RegisterInstance();

	UFUNCTION(BlueprintCallable)
	virtual void SetupComponents(const FCharacterCharacteristics InCharacterCharacteristics, const FWeaponCharacteristics InWeaponCharacteristics, const FProjectileCharacteristics InProjectileCharacteristics, const TArray<TSubclassOf<UProjectileEffect>> ProjectileEffects);

	virtual void InitializeCharacterVariables();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// --- ACTIONS
	void Move(const FInputActionValue& Value);

	void Shoot(const FInputActionValue& Value);

	void StopShoot(const FInputActionValue& Value);

	void AutoFire(const FInputActionValue& Value);

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

	FORCEINLINE FCharacterCharacteristics GetCharacteristics() const { return CharacterCharacteristics; }



	// --- SETTERS
	UFUNCTION()
	virtual void UpdateCharacteristics(FCharacterCharacteristics& Other);
};

