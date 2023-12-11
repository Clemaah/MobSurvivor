// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ProjectileCharacteristics.h"
#include "ProjectileData.generated.h"

class UProjectileEffect;
class AProgGameplayProtoCharacter;
class UWeaponComponent;
/**
 *
 */

USTRUCT(BlueprintType)
struct PROGGAMEPLAYPROTO_API FProjectileLevel
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FProjectileCharacteristics Characteristics;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (ClampMin = 0))
	int Price;
};

UCLASS(BlueprintType)
class PROGGAMEPLAYPROTO_API UProjectileData : public UDataAsset
{
	GENERATED_BODY()

public:
	UProjectileData();

	UFUNCTION(BlueprintPure)
	TMap<FString, float> GetMap(const int Level);

	UFUNCTION(BlueprintPure)
	FProjectileCharacteristics GetLevelCharacteristics(const int Level);

	UFUNCTION(BlueprintPure)
	int GetLevelPrice(const int Level);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meta")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meta", Meta = (MultiLine = true))
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Characteristics", Meta = (EditFixedOrder, ToolTip = "The first level contains base characteristics. Next ones contains modifiers."))
	TArray<FProjectileLevel> Levels;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Effects")
	TArray<TSubclassOf<UProjectileEffect>> Effects;

public:
	UFUNCTION(BlueprintCallable)
	virtual void Apply(AProgGameplayProtoCharacter* Character, UWeaponComponent* Weapon);

	virtual void ApplyEffects(AProgGameplayProtoCharacter* Character, UWeaponComponent* Weapon);
};
