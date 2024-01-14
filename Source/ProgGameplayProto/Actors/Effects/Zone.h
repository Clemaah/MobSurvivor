#pragma once
#include "Zone.generated.h"

UCLASS()
class PROGGAMEPLAYPROTO_API AZone : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* Sphere1;

	AZone();
public:
	UFUNCTION()
	virtual void CheckForCollisions();

	UFUNCTION()
	virtual void HitSomething(AActor* OtherActor);

	UFUNCTION()
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere)
	float DesiredIntensity;

	UPROPERTY(VisibleAnywhere)
	AActor* LastActor;
};

