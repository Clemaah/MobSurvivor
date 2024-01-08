// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "ProjectileCharacteristics.h"
#include "ProgGameplayProto/DataAssets/PlayerGPE.h"

#include "ProjectileData.generated.h"

class AProjectile;
class UProjectileEffect;
class AMobSurvivorCharacter;
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
class PROGGAMEPLAYPROTO_API UProjectileData : public UDataAsset, public IPlayerGPE
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meta")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meta", Meta = (MultiLine = true))
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	TSubclassOf<AProjectile> ProjectileToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Characteristics", Meta = (EditFixedOrder, ToolTip = "The first level contains base characteristics. Next ones contains modifiers."))
	TArray<FProjectileLevel> Levels;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Effects")
	TArray<TSubclassOf<UProjectileEffect>> Effects;

	UProjectileData();

	UFUNCTION(BlueprintCallable)
	virtual TArray<FDisplayableCharacteristic> GetDisplayableCharacteristics_Implementation(const int Level) override;

	UFUNCTION(BlueprintCallable)
	virtual int GetLevelPrice_Implementation(const int Level) override;

	UFUNCTION(BlueprintCallable)
	virtual FText GetName_Implementation() override;

	UFUNCTION(BlueprintCallable)
	virtual FText GetDescription_Implementation() override;

	UFUNCTION(BlueprintCallable)
	virtual FProjectileCharacteristics GetCurrentCharacteristics(const int Level);
};
