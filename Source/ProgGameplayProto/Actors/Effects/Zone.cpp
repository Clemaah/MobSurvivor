#include "Zone.h"

#include "Components/SphereComponent.h"
#include "ProgGameplayProto/ActorComponents/HealthComponent.h"

AZone::AZone()
{
	DesiredIntensity = 3000.0f;

	Sphere1 = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere1"));
	Sphere1->InitSphereRadius(250.0f);
	RootComponent = Sphere1;
}

void AZone::BeginPlay()
{
	CheckForCollisions();
	Destroy();
}

void AZone::CheckForCollisions()
{
	TArray<FHitResult> outHits;
	const FCollisionShape shape = FCollisionShape::MakeSphere(Sphere1->GetScaledSphereRadius());
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	GetWorld()->SweepMultiByChannel(outHits, GetActorLocation(), GetActorLocation(), FQuat::Identity, ECC_EngineTraceChannel2, shape, params);

	for (auto outHit : outHits)
	{
		if (IsValid(LastActor))
		{
			if (LastActor == outHit.GetActor()) continue;
		}
		HitSomething(outHit.GetActor());
	}
}

void AZone::HitSomething(AActor* OtherActor)
{
	LastActor = OtherActor;

	UHealthComponent* HealthComponent = OtherActor->FindComponentByClass<UHealthComponent>();

	if (IsValid(HealthComponent))
	{
		HealthComponent->AddHealth(-5);

	}
}