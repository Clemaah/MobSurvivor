// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Drop.h"
#include "ExperienceDrop.generated.h"

/**
 *
 */
UCLASS()
class PROGGAMEPLAYPROTO_API AExperienceDrop : public ADrop
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ExperienceAmount;

protected:
	virtual void Collect() override;
};
