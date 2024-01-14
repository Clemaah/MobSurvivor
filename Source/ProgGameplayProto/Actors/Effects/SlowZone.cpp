#include "SlowZone.h"

#include "ProgGameplayProto/Actors/Enemy.h"
#include "Components/PointLightComponent.h"
#include "Components/SphereComponent.h"
#include "ProgGameplayProto/ActorComponents/HealthComponent.h"

ASlowZone::ASlowZone()
{

	Sphere1 = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere1"));
	Sphere1->InitSphereRadius(250.0f);
	RootComponent = Sphere1;
}

void ASlowZone::BeginPlay()
{
	CheckForCollisions();
}

void ASlowZone::CheckForCollisions()
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

void ASlowZone::HitSomething(AActor* OtherActor)
{
	LastActor = OtherActor;

	AEnemy* Target = (AEnemy*)LastActor;
	Target->MovingSpeed *= 0.8;
	
}