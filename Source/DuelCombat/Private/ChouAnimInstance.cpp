// Fill out your copyright notice in the Description page of Project Settings.


#include "ChouAnimInstance.h"
#include "ChouCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Acts like tick for animations and get speed
void UChouAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (ChouCharacter == nullptr)
	{
		ChouCharacter = Cast<AChouCharacter>(TryGetPawnOwner());
	}
	if (ChouCharacter)
	{
		// Get speed of character from velocity
		FVector Velocity = ChouCharacter->GetVelocity();
		Velocity.Z = 0;
		Speed = Velocity.Size();

		bIsInAir = ChouCharacter->GetCharacterMovement()->IsFalling();

		// Get offset yaw for player in blend spaces
		FRotator const AimRotation = ChouCharacter->GetBaseAimRotation();
		FRotator const MovementRotation = UKismetMathLibrary::MakeRotFromX(ChouCharacter->GetVelocity());

		Direction = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;
	}
}

// Acts like begin play create reference to character
void UChouAnimInstance::NativeInitializeAnimation()
{
	ChouCharacter = Cast<AChouCharacter>(TryGetPawnOwner());
}
