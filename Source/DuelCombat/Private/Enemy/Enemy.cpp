// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Enemy.h"

// Sets default values
AEnemy::AEnemy() :
	BaseDamage(5.f),
	Health(100.f),
	MaxHealth(100.f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::HitInterface_Implementation(FHitResult HitResult)
{

}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EvenInstigator, AActor* DamageCauser)
{
	if (Health - DamageAmount <= 0.f)
	{
		Health = 0.f;
		// call blueprint function to play death montage and clean things up
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Enemy died!"));
	}
	else
	{
		Health -= DamageAmount;
	}

	return DamageAmount;
}

