#pragma once
#include "SlowZone.generated.h"

UCLASS()
class PROGGAMEPLAYPROTO_API ASlowZone : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* Sphere1;

	ASlowZone();
public:
	UFUNCTION()
	virtual void CheckForCollisions();

	UFUNCTION()
	virtual void HitSomething(AActor* OtherActor);

	UFUNCTION()
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	AActor* LastActor;
};

