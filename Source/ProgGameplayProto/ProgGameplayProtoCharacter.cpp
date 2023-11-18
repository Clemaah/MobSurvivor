// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProgGameplayProtoCharacter.h"

#include "DiffUtils.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ExperienceComponent.h"
#include "HealthComponent.h"
#include "InputActionValue.h"
#include "Bonuses/BonusData.h"
#include "Components/SphereComponent.h"
#include "Drops/Drop.h"
#include "Weapons/WeaponComponent.h"
#include "Abilities/AbilityComponent.h"
#include "Logging/StructuredLog.h"
#include "Weapons/WeaponData.h"
#include "Weapons/WeaponProjectile.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AProgGameplayProtoCharacter

AProgGameplayProtoCharacter* AProgGameplayProtoCharacter::Instance = nullptr;
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

	Ability = CreateDefaultSubobject<UAbilityComponent>("Ability");

	Health = CreateDefaultSubobject<UHealthComponent>("Health");

	Experience = CreateDefaultSubobject<UExperienceComponent>("Experience");

	DropsCollector = CreateDefaultSubobject<USphereComponent>("Drops Collector");
	DropsCollector->SetRelativeLocation(FVector(0, 0, -90));
	DropsCollector->SetupAttachment(GetCapsuleComponent());
}

bool AProgGameplayProtoCharacter::WantsToShoot()
{
	return bIsHoldingShoot || bIsAutoFire;
}

void AProgGameplayProtoCharacter::SetupDefaultComponents()
{
	SetupDefaultWeapon();
	SetupDefaultAbility();

	for (int32 i = 0; i < DefaultBonuses.Num(); i++)
	{
		DefaultBonuses[i]->Apply(this, Weapon, Ability);
	}
}

void AProgGameplayProtoCharacter::SetupDefaultWeapon()
{
	Weapon->SetData(DefaultWeaponData);
	Weapon->InitializeWeapon(this);
}

void AProgGameplayProtoCharacter::SetupDefaultAbility()
{
	Ability->SetData(DefaultAbilityData);
	Ability->InitializeAbility(this);
}

void AProgGameplayProtoCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	RegisterInstance();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	//Setup Components
	SetupDefaultComponents();

	DropsCollector->OnComponentBeginOverlap.AddDynamic(this, &AProgGameplayProtoCharacter::OnDropsCollectorBeginOverlap);
}

void AProgGameplayProtoCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProgGameplayProtoCharacter::RegisterInstance()
{
	Instance = this;
}

void AProgGameplayProtoCharacter::OnDropsCollectorBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADrop* drop = Cast<ADrop>(OtherActor);

	if (!IsValid(drop)) return;

	drop->StartCollection(this);
}

//////////////////////////////////////////////////////////////////////////
// Input

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