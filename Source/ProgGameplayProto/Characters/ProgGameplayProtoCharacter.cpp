// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProgGameplayProtoCharacter.h"

#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/SphereComponent.h"
#include "ProgGameplayProto/Drops/Drop.h"
#include "ProgGameplayProto/Weapons/WeaponComponent.h"
#include "ProgGameplayProto/Characters/CharacterData.h"
#include "ProgGameplayProto/HealthComponent.h"
#include "ProgGameplayProto/ExperienceComponent.h"
#include "ProgGameplayProto/Projectiles/ProjectileData.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);



//////////////////////////////////////////////////////////////////////////
// --- INSTANCE

AProgGameplayProtoCharacter* AProgGameplayProtoCharacter::Instance = nullptr;



//////////////////////////////////////////////////////////////////////////
// --- INITIALIZATION

AProgGameplayProtoCharacter::AProgGameplayProtoCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	Weapon = CreateDefaultSubobject<UWeaponComponent>("Weapon");

	Health = CreateDefaultSubobject<UHealthComponent>("Health");

	Experience = CreateDefaultSubobject<UExperienceComponent>("Experience");

	DropsCollector = CreateDefaultSubobject<USphereComponent>("Drops Collector");
	DropsCollector->SetRelativeLocation(FVector(0, 0, -90));
	DropsCollector->SetupAttachment(GetCapsuleComponent());

	RegisterInstance();
}

void AProgGameplayProtoCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	DropsCollector->OnComponentBeginOverlap.AddDynamic(this, &AProgGameplayProtoCharacter::OnDropsCollectorBeginOverlap);
}

void AProgGameplayProtoCharacter::RegisterInstance()
{
	Instance = this;
}

void AProgGameplayProtoCharacter::SetupComponents(const FCharacterCharacteristics InCharacterCharacteristics, const FWeaponCharacteristics InWeaponCharacteristics, const FProjectileCharacteristics InProjectileCharacteristics)
{
	CharacterCharacteristics = InCharacterCharacteristics;
	Weapon->InitializeWeapon(this, InWeaponCharacteristics, InProjectileCharacteristics);

	InitializeCharacterVariables();
}

void AProgGameplayProtoCharacter::InitializeCharacterVariables()
{
	DropsCollector->SetSphereRadius(CharacterCharacteristics.DropCollectorRadius * 100);
	Health->InitializeHealth(CharacterCharacteristics.MaxHealth, CharacterCharacteristics.RegenerationRate);
	GetCharacterMovement()->MaxWalkSpeed = CharacterCharacteristics.Speed * 1000;
}

void AProgGameplayProtoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AProgGameplayProtoCharacter::Move);

		//Shooting
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &AProgGameplayProtoCharacter::Shoot);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Completed, this, &AProgGameplayProtoCharacter::StopShoot);
		EnhancedInputComponent->BindAction(AutoFireAction, ETriggerEvent::Started, this, &AProgGameplayProtoCharacter::AutoFire);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}



//////////////////////////////////////////////////////////////////////////
// --- ACTIONS

void AProgGameplayProtoCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AProgGameplayProtoCharacter::Shoot(const FInputActionValue& Value)
{
	bIsHoldingShoot = true;
}

void AProgGameplayProtoCharacter::StopShoot(const FInputActionValue& Value)
{
	bIsHoldingShoot = false;
}

void AProgGameplayProtoCharacter::AutoFire(const FInputActionValue& Value)
{
	bIsAutoFire = !bIsAutoFire;
}

bool AProgGameplayProtoCharacter::WantsToShoot()
{
	return bIsHoldingShoot || bIsAutoFire;
}



//////////////////////////////////////////////////////////////////////////
// --- EVENTS

void AProgGameplayProtoCharacter::OnDropsCollectorBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADrop* drop = Cast<ADrop>(OtherActor);

	if (!IsValid(drop)) return;

	drop->StartCollection(this);
}



//////////////////////////////////////////////////////////////////////////
// --- SETTERS

void AProgGameplayProtoCharacter::UpdateCharacteristics(FCharacterCharacteristics& CharacterBonuses)
{
	CharacterCharacteristics += CharacterBonuses;

	DropsCollector->SetSphereRadius(CharacterCharacteristics.DropCollectorRadius * 100);
	Health->SetMaxHealth(CharacterCharacteristics.MaxHealth);
	Health->SetRegenerationRate(CharacterCharacteristics.RegenerationRate);
	GetCharacterMovement()->MaxWalkSpeed = CharacterCharacteristics.Speed * 1000;
}