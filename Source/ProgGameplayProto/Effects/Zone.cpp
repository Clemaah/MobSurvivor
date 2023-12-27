#include "Zone.h"

#include "Components/PointLightComponent.h"
#include "Components/SphereComponent.h"
#include <ProgGameplayProto/Characters/ProgGameplayProtoCharacter.h>

#include "ProgGameplayProto/HealthComponent.h"
#include "ProgGameplayProto/ProjectileInteraction.h"

AZone::AZone()
{
	DesiredIntensity = 3000.0f;

	PointLight1 = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight1"));
	PointLight1->Intensity = DesiredIntensity;
	PointLight1->SetVisibleFlag(true);
	RootComponent = PointLight1;

	Sphere1 = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere1"));
	Sphere1->InitSphereRadius(250.0f);
	Sphere1->SetupAttachment(RootComponent);

	Sphere1->OnComponentEndOverlap.AddDynamic(this, &AZone::OnOverlapEnd);
}

void AZone::CheckForCollisions(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TArray<FHitResult> outHits;
	const FCollisionShape shape = FCollisionShape::MakeSphere(Sphere1->GetScaledSphereRadius());
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	GetWorld()->SweepMultiByChannel(outHits, GetActorLocation(), GetActorLocation(), FQuat::Identity, ECC_EngineTraceChannel2, shape, params);

	for (auto outHit : outHits)
	{
		HitSomething(outHit.GetActor());
	}
}

void AZone::HitSomething(AActor* OtherActor)
{
	UHealthComponent* HealthComponent = OtherActor->FindComponentByClass<UHealthComponent>();

	if (IsValid(HealthComponent))
	{
		HealthComponent->AddHealth(-10);
	}
}

void AZone::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		ToggleLight();
	}
}

void AZone::ToggleLight()
{
	PointLight1->ToggleVisibility();
}