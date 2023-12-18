// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "EnemyData.h"
#include "Components/CapsuleComponent.h"
#include "ProgGameplayProto/System/GameUtils.h"
#include "ProgGameplayProto/HealthComponent.h"
//#include "GameFramework/CharacterMovementComponent.h"
#include "ProgGameplayProto/Characters/ProgGameplayProtoCharacter.h"
#include "ProgGameplayProto/Drops/EnemyDropperComponent.h"
#include "ProgGameplayProto/System/MobSurvivorGameInstance.h"
#include "ProgGameplayProto/Weapons/WeaponComponent.h"

//////////////////////////////////////////////////////////////////////////
// --- INITIALIZATION

AEnemy::AEnemy()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UCapsuleComponent>("Collision");
	SetRootComponent(Collision);

	Health = CreateDefaultSubobject<UHealthComponent>("Health");

	Weapon = CreateDefaultSubobject<UWeaponComponent>("Weapon");

	Dropper = CreateDefaultSubobject<UEnemyDropperComponent>("Dropper");
	Dropper->SetupAttachment(Collision);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	Health->OnHealthDie.AddDynamic(this, &AEnemy::Die);
}

void AEnemy::MoveTowardPlayer(float DeltaTime)
{
	const AProgGameplayProtoCharacter* player = UGameUtils::GetMainCharacter();

	if (!IsValid(player)) return;

	FVector direction = player->GetActorLocation() - GetActorLocation();
	direction.Z = 0;
	direction.Normalize();

	
	if (EnemyData->WeaponData && (GetActorLocation() - player->GetActorLocation()).Size() < EnemyData->RangedAttackMaxRange)
	{
		Weapon->bWantsToShoot = true;
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Attack !"));
	}
	else
	{
		FVector movement = direction * MoveSpeed * DeltaTime;
		AddActorWorldOffset(movement);
		Weapon->bWantsToShoot = false;
	}

}

void AEnemy::Die()
{
	UMobSurvivorGameInstance* GameInstance = UGameUtils::GetGameInstance(GetWorld());

	if (IsValid(GameInstance))
		GameInstance->GamePoints += Points;

	Destroy();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveTowardPlayer(DeltaTime);
}

void AEnemy::SetupComponents(/*const FEnemyCharacteristics InCharacterCharacteristics,*/ const FWeaponCharacteristics InWeaponCharacteristics, const FProjectileCharacteristics InProjectileCharacteristics, const TArray<TSubclassOf<UProjectileEffect>> ProjectileEffects)
{
	//EnemyCharacteristics = InCharacterCharacteristics;
	Weapon->InitializeWeapon(this,InWeaponCharacteristics, InProjectileCharacteristics, ProjectileEffects);

	//InitializeCharacterVariables(); 
}

/*void AEnemy::InitializeCharacterVariables()
{
	DropsCollector->SetSphereRadius(EnemyCharacteristics.DropCollectorRadius * 100);
	Health->InitializeHealth(EnemyCharacteristics.MaxHealth, EnemyCharacteristics.RegenerationRate);
	GetCharacterMovement()->MaxWalkSpeed = EnemyCharacteristics.Speed * 1000;
}*/

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::TryAttacking(AActor* Target)
{
	if (!Target->IsA(AProgGameplayProtoCharacter::StaticClass())) return;

	UHealthComponent* targetHealth = Target->FindComponentByClass<UHealthComponent>();

	if (!IsValid(targetHealth)) return;

	targetHealth->HitByAttack(Damages, this);

	Attack_BP(Target);
}

/*void AEnemy::UpdateCharacteristics(FEnemyCharacteristics& CharacterBonuses)
{
	EnemyCharacteristics += CharacterBonuses;

	Health->SetMaxHealth(EnemyCharacteristics.Health);
	GetMovementComponent()->MaxWalkSpeed = EnemyCharacteristics.Speed * 1000;
}*/