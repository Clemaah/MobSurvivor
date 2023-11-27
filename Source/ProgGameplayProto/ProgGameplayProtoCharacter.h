// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "ProgGameplayProtoCharacter.generated.h"

class USphereComponent;
class UExperienceComponent;
class UHealthComponent;
class UBonusData;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UWeaponComponent;
class UWeaponData;
class AWeaponProjectile;
class UPersonaComponent;
class UPersonaData;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config = Game)
class AProgGameplayProtoCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AutoFireAction;

public:
	AProgGameplayProtoCharacter();

	static AProgGameplayProtoCharacter* Instance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapons & Persona")
	TSubclassOf<AWeaponProjectile> WeaponProjectileToSpawn;

	virtual bool WantsToShoot();

	void SetupComponents();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapons & Persona")
	USphereComponent* DropsCollector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapons & Persona")
	TArray<UBonusData*> DefaultBonuses;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapons & Persona")
	UWeaponData* DefaultWeaponData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapons & Persona")
	UPersonaData* DefaultPersonaData;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Weapons & Persona")
	UWeaponData* SelectedWeaponData;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Weapons & Persona")
	UPersonaData* SelectedPersonaData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UHealthComponent* Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UExperienceComponent* Experience;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UWeaponComponent* Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPersonaComponent* Persona;

	bool bIsHoldingShoot = false;
	bool bIsAutoFire = false;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	void Shoot(const FInputActionValue& Value);

	void StopShoot(const FInputActionValue& Value);

	void AutoFire(const FInputActionValue& Value);


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void RegisterInstance();

	UFUNCTION()
	virtual void OnDropsCollectorBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE UExperienceComponent* GetExperience() const { return Experience; }

	FORCEINLINE UHealthComponent* GetHealth() const { return Health; }

	FORCEINLINE UWeaponComponent* GetWeapon() const { return Weapon; }

	FORCEINLINE UPersonaComponent* GetPersona() const { return Persona; }

	FORCEINLINE void SetDropCollectorRadius(float NewRadius) const { DropsCollector->SetSphereRadius(NewRadius); }
};

