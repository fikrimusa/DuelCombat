// Developed by Fikri

#include "Enemy/Enemy.h"

AEnemy::AEnemy() :
	BaseDamage(5.f),
	Health(100.f),
	MaxHealth(100.f)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemy::HitInterface_Implementation(FHitResult HitResult)
{
	// Handle hit logic here
}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EvenInstigator, AActor* DamageCauser)
{
	if (Health - DamageAmount <= 0.f)
	{
		Health = 0.f;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Enemy died!"));
	}
	else
	{
		Health -= DamageAmount;
	}

	return DamageAmount;
}
