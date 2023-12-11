
#include "SniperBonusData.h"

#include "ProgGameplayProto/Characters/ProgGameplayProtoCharacter.h"
#include "ProgGameplayProto/Effects/SniperEffect.h"
#include "ProgGameplayProto/Weapons/WeaponComponent.h"

void USniperProjectileData::Apply(AProgGameplayProtoCharacter* Character, UWeaponComponent* Weapon)
{
	Super::Apply(Character, Weapon);

	USniperEffect* effect = NewObject<USniperEffect>(this, SniperEffect);
	effect->NumberOfEnemyToPierce = NumberOfEnemyToPierce;

	Weapon->AddEffect(effect);
}