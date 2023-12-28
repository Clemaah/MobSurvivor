#pragma once
#include "Zone.generated.h"

UCLASS()
class PROGGAMEPLAYPROTO_API AZone : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere)
	class UPointLightComponent* PointLight1;

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

	UFUNCTION()
	virtual void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	virtual void ToggleLight();

	UPROPERTY(VisibleAnywhere)
	float DesiredIntensity;
};

