// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectileInteraction.generated.h"

class AProjectile;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHitDelegate, const FRotator&, ProjectileRotation, const float, ProjectileSpeed);

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

	virtual void HitByProjectile(AProjectile* Projectile);

	UPROPERTY(BlueprintAssignable)
	FHitDelegate OnHitByProjectile;
};
