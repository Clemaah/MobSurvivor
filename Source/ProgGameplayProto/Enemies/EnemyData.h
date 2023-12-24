// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnemyData.generated.h"


class UCharacterData;
class UWeaponData;
class UProjectileData;


UENUM(BlueprintType)
enum class EEnemyType : uint8 {
	CAC		 UMETA(DisplayName = "CAC"),
	Distance    UMETA(DisplayName = "Distance"),
	Weak     UMETA(DisplayName = "Weak"),
	Big     UMETA(DisplayName = "Big"),
	Boss     UMETA(DisplayName = "Boss"),
};
/**
 * 
 */
UCLASS()
class PROGGAMEPLAYPROTO_API UEnemyData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
		EEnemyType EnemyType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy", Meta = (MultiLine = true))
		FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
		int Points;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
		float HitPoints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
		float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
		float Damage_CAC;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
		float RangedAttackMaxRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
		UWeaponData* WeaponData;
};


