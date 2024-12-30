// Developed by Fikri

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HitInterface.h"
#include "Enemy.generated.h"

UCLASS()
class DUELCOMBAT_API AEnemy : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this enemy character's properties (e.g., health, damage).
	AEnemy();

	// Called every frame to update the enemy's state (e.g., movement, AI).
	virtual void Tick(float DeltaTime) override;

	// Implementation of the HitInterface. Handles what happens when the enemy is hit.
	virtual void HitInterface_Implementation(FHitResult HitResult) override;

	// Called when the enemy takes damage. Updates health and handles damage logic.
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EvenInstigator, AActor* DamageCauser) override;

protected:
	// Called when the game starts or when the enemy is spawned in the world.
	virtual void BeginPlay() override;

private:
	// Base damage the enemy inflicts with attacks.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float BaseDamage;

	// Current health of the enemy.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float Health;

	// Maximum health the enemy can have.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float MaxHealth;
};
