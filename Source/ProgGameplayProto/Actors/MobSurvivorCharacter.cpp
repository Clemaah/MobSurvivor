// Copyright Epic Games, Inc. All Rights Reserved.

#include "MobSurvivorCharacter.h"


#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ProgGameplayProto/ActorComponents/ExperienceComponent.h"
#include "ProgGameplayProto/ActorComponents/HealthComponent.h"
#include "ProgGameplayProto/ActorComponents/WeaponComponent.h"

#include "ProgGameplayProto/Actors/Drops/Drop.h"

#include "ProgGameplayProto/DataAssets/PersonaCharacteristics.h"
#include "ProgGameplayProto/DataAssets/Characters/CharacterCharacteristics.h"
#include "ProgGameplayProto/DataAssets/Projectiles/ProjectileCharacteristics.h"
#include "ProgGameplayProto/DataAssets/Weapons/WeaponCharacteristics.h"

DEFINE_LOG_CATEGORY(LogCharacter);

//////////////////////////////////////////////////////////////////////////
// --- INSTANCE

AMobSurvivorCharacter* AMobSurvivorCharacter::Instance = nullptr;



//////////////////////////////////////////////////////////////////////////
// --- INITIALIZATION

AMobSurvivorCharacter::AMobSurvivorCharacter()
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
	CameraBoom->TargetArmLength = 800.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = false; // Rotate the arm based on the controller

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

	DropsCollectorMesh = CreateDefaultSubobject<UStaticMeshComponent>("Drops Collector Mesh");
	DropsCollectorMesh->SetRelativeScale3D(FVector(2, 2, 0.01));
	DropsCollectorMesh->SetupAttachment(DropsCollector);

	AMobSurvivorCharacter::RegisterInstance();
}

void AMobSurvivorCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	DropsCollector->OnComponentBeginOverlap.AddDynamic(this, &AMobSurvivorCharacter::OnDropsCollectorBeginOverlap);
}

void AMobSurvivorCharacter::RegisterInstance()
{
	Instance = this;
}

void AMobSurvivorCharacter::SetupComponents(
	const FPersonaCharacteristics InPersonaCharacteristics,
	const FCharacterCharacteristics InCharacterCharacteristics,
	const FWeaponCharacteristics InWeaponCharacteristics, 
	const FProjectileCharacteristics InProjectileCharacteristics, 
	const TSubclassOf<AProjectile> InProjectileToSpawn, 
	const TArray<TSubclassOf<UProjectileEffect>> ProjectileEffects)
{
	PersonaCharacteristics = InPersonaCharacteristics;
	CharacterCharacteristics = InCharacterCharacteristics;
	Weapon->InitializeWeapon(this, &PersonaCharacteristics, InWeaponCharacteristics, InProjectileCharacteristics, InProjectileToSpawn, ProjectileEffects);

	InitializeCharacterVariables();
}

void AMobSurvivorCharacter::InitializeCharacterVariables()
{
	DropsCollector->SetSphereRadius(CharacterCharacteristics.DropCollectorRadius * 100);
	DropsCollectorMesh->SetRelativeScale3D(FVector(CharacterCharacteristics.DropCollectorRadius * 2, CharacterCharacteristics.DropCollectorRadius * 2, 0.01));

	Health->InitializeHealth(PersonaCharacteristics.MaxHealth, PersonaCharacteristics.RegenerationRate);

	GetCharacterMovement()->MaxWalkSpeed = PersonaCharacteristics.Speed * 1000;
	CameraBoom->TargetArmLength = PersonaCharacteristics.Speed * 500 + 700;
}

void AMobSurvivorCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMobSurvivorCharacter::Move);

		//Shooting
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &AMobSurvivorCharacter::Shoot);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Completed, this, &AMobSurvivorCharacter::StopShoot);
		EnhancedInputComponent->BindAction(AutoFireAction, ETriggerEvent::Started, this, &AMobSurvivorCharacter::AutoFire);
	}
	else
		UE_LOG(LogCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
}



//////////////////////////////////////////////////////////////////////////
// --- ACTIONS
void AMobSurvivorCharacter::Tick(float DeltaSeconds)
{
	if (bWantsToShoot && Weapon->bCanShoot)
		Weapon->Shoot(GetMouseDirection().Rotation());
}

void AMobSurvivorCharacter::Move(const FInputActionValue& Value)
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

void AMobSurvivorCharacter::Shoot(const FInputActionValue& Value)
{
	bIsHoldingShoot = true;
	WantsToShoot();
}

void AMobSurvivorCharacter::StopShoot(const FInputActionValue& Value)
{
	bIsHoldingShoot = false;
	WantsToShoot();
}

void AMobSurvivorCharacter::AutoFire(const FInputActionValue& Value)
{
	bIsAutoFire = !bIsAutoFire;
	WantsToShoot();
}

void AMobSurvivorCharacter::WantsToShoot()
{
	bWantsToShoot = bIsHoldingShoot || bIsAutoFire;
}



//////////////////////////////////////////////////////////////////////////
// --- EVENTS

void AMobSurvivorCharacter::OnDropsCollectorBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADrop* drop = Cast<ADrop>(OtherActor);

	if (!IsValid(drop)) return;

	drop->StartCollection(this);
}



//////////////////////////////////////////////////////////////////////////
// --- SETTERS

void AMobSurvivorCharacter::UpdateCharacteristics(FPersonaCharacteristics& PersonaBonuses, FCharacterCharacteristics& CharacterBonuses)
{
	PersonaCharacteristics += PersonaBonuses;
	CharacterCharacteristics += CharacterBonuses;

	DropsCollector->SetSphereRadius(CharacterCharacteristics.DropCollectorRadius * 100);
	DropsCollectorMesh->SetRelativeScale3D(FVector(CharacterCharacteristics.DropCollectorRadius * 2, CharacterCharacteristics.DropCollectorRadius * 2, 0.01));
	Health->SetMaxHealth(PersonaCharacteristics.MaxHealth);
	Health->SetRegenerationRate(PersonaCharacteristics.RegenerationRate);
	GetCharacterMovement()->MaxWalkSpeed = PersonaCharacteristics.Speed * 1000;
}

FVector AMobSurvivorCharacter::GetMouseDirection()
{
	FVector mouseLocation;
	FVector mouseDirection;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->DeprojectMousePositionToWorld(mouseLocation, mouseDirection);

	FHitResult outHit;
	FVector endTraceLocation = mouseLocation + mouseDirection * 10000;
	FCollisionObjectQueryParams params;
	params.AddObjectTypesToQuery(ECC_WorldStatic);
	GetWorld()->LineTraceSingleByObjectType(outHit, mouseLocation, endTraceLocation, params);

	if (outHit.bBlockingHit)
	{
		FVector neutralCharacterLocation = GetActorLocation();
		neutralCharacterLocation.Z = 0;
		FVector neutralMouseLocation = outHit.Location;
		neutralMouseLocation.Z = 0;

		FVector direction = neutralMouseLocation - neutralCharacterLocation;
		direction.Normalize();

		return direction;
	}

	return GetActorForwardVector();
}