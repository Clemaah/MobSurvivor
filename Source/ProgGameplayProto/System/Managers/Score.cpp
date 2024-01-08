#include "Score.h"

void UScore::Initialization(const FString& inPseudo, const FString& inCharacter, const FString& InWeapon,
	const FString& InProjectile, float InScore)
{
	Pseudo = inPseudo;
	Character = inCharacter;
	Weapon = InWeapon;
	Projectile = InProjectile;
	Score = InScore;
}
