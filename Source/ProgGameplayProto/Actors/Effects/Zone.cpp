#include "Zone.h"

#include "Components/PointLightComponent.h"
#include "Components/SphereComponent.h"
#include "ProgGameplayProto/ActorComponents/HealthComponent.h"

AZone::AZone()
{
	DesiredIntensity = 3000.0f;

	//PointLight1 = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight1"));
	//PointLight1->Intensity = DesiredIntensity;
	//PointLight1->SetVisibleFlag(true);
	//RootComponent = PointLight1;

	Sphere1 = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere1"));
	Sphere1->InitSphereRadius(250.0f);
	RootComponent = Sphere1;

	//Sphere1->OnComponentEndOverlap.AddDynamic(this, &AZone::OnOverlapEnd);
}

void AZone::BeginPlay()
{
	CheckForCollisions();
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
		HealthComponent->AddHealth(-10);

	}
}