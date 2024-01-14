#include "ShooterComponent.h"

#include "Kismet/GameplayStatics.h"
#include "ProgGameplayProto/Actors/MobSurvivorCharacter.h"

UShooterComponent::UShooterComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UShooterComponent::InitializeShooter(AMobSurvivorCharacter* InCharacter, UWeaponComponent* InWeapon)
{
	Character = InCharacter;
	Weapon = InWeapon;
}

void UShooterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	UpdateShootingDirection();

	if (bWantsToShoot)
		Weapon->TryShooting(ShootingDirection);
}


void UShooterComponent::UpdateShootingDirection()
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
		FVector neutralCharacterLocation = Character->GetActorLocation();
		neutralCharacterLocation.Z = 0;
		FVector neutralMouseLocation = outHit.Location;
		neutralMouseLocation.Z = 0;

		FVector direction = neutralMouseLocation - neutralCharacterLocation;

		ShootingDirection = direction.Rotation();
	}

	else
		ShootingDirection = Character->GetActorForwardVector().Rotation();
}

void UShooterComponent::ToggleWantsToShoot(bool Activate)
{
	bWantsToShoot = Activate;
	OnWantsToShootDelegate.Broadcast(bWantsToShoot);
}
