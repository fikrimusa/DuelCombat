// Developed by Fikri

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

class AEnemy;

/**
 * UEnemyAnimInstance handles the animation properties for enemy characters.
 * It updates and manages the enemy's animation states based on movement and actions.
 */
UCLASS()
class DUELCOMBAT_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	// Updates animation properties such as speed and direction based on the enemy's movement.
	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties(float DeltaTime);

private:
	// Reference to the enemy character to access movement and state data for animations.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AEnemy* Enemy;

	// The enemy's current movement speed used for transitioning between animation states (e.g., running, walking).
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float Speed;

	// The enemy's movement direction, used for animating the enemy's facing direction.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float Direction;
};
