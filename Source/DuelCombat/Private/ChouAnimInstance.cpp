// Developed by Fikri

#include "ChouAnimInstance.h"
#include "ChouCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Update animation properties every tick (acts like the tick for animations)
void UChouAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	// If the character reference is not set, get it from the pawn owner
	if (ChouCharacter == nullptr)
	{
		ChouCharacter = Cast<AChouCharacter>(TryGetPawnOwner());
	}

	// If the ChouCharacter reference is valid, update properties
	if (ChouCharacter)
	{
		// Get the velocity of the character and calculate speed (ignore Z-axis for movement)
		FVector Velocity = ChouCharacter->GetVelocity();
		Velocity.Z = 0;  // We don't need vertical velocity for speed
		Speed = Velocity.Size(); // The size of the vector represents the speed

		// Check if the character is in the air (falling or jumping)
		bIsInAir = ChouCharacter->GetCharacterMovement()->IsFalling();

		// Get the aim rotation (the direction the character is aiming)
		FRotator const AimRotation = ChouCharacter->GetBaseAimRotation();

		// Get the movement rotation (the direction the character is moving)
		FRotator const MovementRotation = UKismetMathLibrary::MakeRotFromX(ChouCharacter->GetVelocity());

		// Calculate the difference in yaw (left/right rotation) between movement and aiming
		Direction = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;
	}
}

// This function is called once, similar to BeginPlay, to initialize references for animations
void UChouAnimInstance::NativeInitializeAnimation()
{
	// Get a reference to the character (the pawn owner of the animation instance)
	ChouCharacter = Cast<AChouCharacter>(TryGetPawnOwner());
}
