// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Drop.h"
#include "ProgGameplayProto/ActorComponents/HealthComponent.h"
#include "ChestDrop.generated.h"


UENUM(BlueprintType)
enum EChestDropState { Closed, Opening, Open };

/**
 *
 */
UCLASS()
class PROGGAMEPLAYPROTO_API AChestDrop : public ADrop
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom|Components")
	UHealthComponent* Health;

public:
	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EChestDropState> State;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int BonusNumberToChoose = 1;

	AChestDrop();

	virtual void BeginPlay() override;

	virtual void StartCollection(AActor* NewTarget) override;

	UFUNCTION()
	void OnUnlock();

	UFUNCTION(BlueprintImplementableEvent)
	void OnCollect();
};
