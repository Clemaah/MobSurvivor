// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectileInteraction.generated.h"

class AWeaponProjectile;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHitDelegate, AWeaponProjectile*, Projectile);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROGGAMEPLAYPROTO_API UProjectileInteraction : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UProjectileInteraction();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void HitByProjectile(AWeaponProjectile* Projectile);

	UPROPERTY(BlueprintAssignable)
	FHitDelegate OnHitByProjectile;
};
