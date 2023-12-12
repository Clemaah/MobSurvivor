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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meta")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meta", Meta = (MultiLine = true))
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Characteristics", Meta = (EditFixedOrder, ToolTip = "The first level contains base characteristics. Next ones contains modifiers."))
	TArray<FProjectileLevel> Levels;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Effects")
	TArray<TSubclassOf<UProjectileEffect>> Effects;

	UProjectileData();

	UFUNCTION(BlueprintPure)
	TMap<FString, float> GetCumulativeLevelsMap(const int Level);

	UFUNCTION(BlueprintPure)
	TMap<FString, float> GetLevelMap(const int Level);

	UFUNCTION(BlueprintPure)
	FProjectileCharacteristics GetCumulativeLevelsCharacteristics(const int Level);

	UFUNCTION(BlueprintPure)
	int GetLevelPrice(const int Level);

	UFUNCTION(BlueprintCallable)
	virtual void Apply(AProgGameplayProtoCharacter* Character, UWeaponComponent* Weapon);

	virtual void ApplyEffects(AProgGameplayProtoCharacter* Character, UWeaponComponent* Weapon);

protected:
	static TMap<FString, float> GetMap(const FProjectileCharacteristics& Characteristics, const int Level);
};
