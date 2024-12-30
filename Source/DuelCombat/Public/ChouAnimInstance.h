// Developed by Fikri

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ChouAnimInstance.generated.h"

class AChouCharacter;

/**
 * UChouAnimInstance handles the animation properties for the Chou character.
 * It updates and manages the character's animation states based on movement and actions.
 */
UCLASS()
class DUELCOMBAT_API UChouAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	// Updates animation properties such as speed and direction based on the character's movement.
	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties(float DeltaTime);

	// Initializes the animation instance, typically used to reference the character.
	virtual void NativeInitializeAnimation() override;

private:
	// Reference to the Chou character for accessing movement and state data.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	AChouCharacter* ChouCharacter;

	// The character's current movement speed used for animation transitions (e.g., running vs walking).
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float Speed;

	// The character's movement direction, used for facing the correct way in animations.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float Direction;

	// Indicates whether the character is in the air (jumping, falling, etc.).
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	bool bIsInAir;

	// Indicates whether the character is blocking (e.g., holding a shield).
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	bool bIsBlocking;
};
