#pragma once
#include "WeaponComponent.h"
#include "ShooterComponent.generated.h"

class AMobSurvivorCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWantsToShootChanged, bool, Activate);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROGGAMEPLAYPROTO_API UShooterComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	// --- CHARACTER REFERENCE
	TObjectPtr<AMobSurvivorCharacter> Character;

	TObjectPtr<UWeaponComponent> Weapon;

	bool bWantsToShoot = false;

public:
	UPROPERTY(BlueprintAssignable)
	FOnWantsToShootChanged OnWantsToShootDelegate;

	UShooterComponent();

	UPROPERTY(BlueprintReadOnly, Category = "Custom")
	FRotator ShootingDirection;

	virtual void InitializeShooter(AMobSurvivorCharacter* InCharacter, UWeaponComponent* InWeapon);

	// --- BEHAVIOUR
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void UpdateShootingDirection();

	void ToggleWantsToShoot(bool Activate);
};
