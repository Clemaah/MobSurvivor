#include "ChestDrop.h"

#include "ProgGameplayProto/ActorComponents/HealthComponent.h"

AChestDrop::AChestDrop()
{
	PrimaryActorTick.bCanEverTick = true;

	Health = CreateDefaultSubobject<UHealthComponent>("Health");
}

void AChestDrop::BeginPlay()
{
	Super::BeginPlay();

	Health->OnHealthDie.AddDynamic(this, &AChestDrop::OnUnlock);
}

void AChestDrop::OnUnlock()
{
	State = Opening;
}

void AChestDrop::StartCollection(AActor* NewTarget)
{
	if (!IsValid(NewTarget)) return;

	if(State == Open)
	{
		CollectingTarget = NewTarget;
		bIsBeingCollected = true;

		OnCollect();

		Destroy();
	}
}