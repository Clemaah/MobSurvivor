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

	UFUNCTION()
	void CheckForCollisions(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void HitSomething(AActor* OtherActor);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void ToggleLight();

	UPROPERTY(VisibleAnywhere)
	float DesiredIntensity;
};

