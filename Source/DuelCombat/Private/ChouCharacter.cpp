// Fill out your copyright notice in the Description page of Project Settings.


#include "ChouCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Layers/LayersSubsystem.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AChouCharacter::AChouCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 400.f;
	SpringArmComponent->bUsePawnControlRotation = true;

	FollowCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	FollowCameraComponent->bUsePawnControlRotation = false;

	// Jump settings
	GetCharacterMovement()->JumpZVelocity = 300.f;
	GetCharacterMovement()->AirControl = 0.1f;

}

// Called when the game starts or when spawned
void AChouCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Add input mapping content
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		//Get local player subsystem
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			//Add input context
			Subsystem->AddMappingContext(InputMapping, 0);

		}

	}
}

void AChouCharacter::Move(const FInputActionValue& InputValue)
{
	FVector2d InputVector = InputValue.Get<FVector2d>();

	if (IsValid(Controller))
	{
		// Get forward direction
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		//Rotation matrix
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Add movement input
		AddMovementInput(ForwardDirection, InputVector.Y);
		AddMovementInput(RightDirection, InputVector.X);
	}

}

void AChouCharacter::Look(const FInputActionValue& InputValue)
{
	FVector2d InputVector = InputValue.Get<FVector2d>();

	if (IsValid(Controller))
	{
		AddControllerYawInput(InputVector.X);
		AddControllerPitchInput(InputVector.Y);
	}
}

void AChouCharacter::Jump()
{
	//Call parent class jump function
	Super::Jump();

	if (GetCharacterMovement()->IsMovingOnGround())
	{
		// Get current forward velocity
		FVector ForwardVelocity = GetVelocity();
		ForwardVelocity.Z = 0;

		// Define jump vertical velocity
		float JumpVerticalVelocity = GetCharacterMovement()->JumpZVelocity;

		// Combine current forward velocity with jump vertical velocity
		FVector JumpVelocity = ForwardVelocity + FVector(0, 0, JumpVerticalVelocity);

		// Launch character with the combined velocity
		LaunchCharacter(JumpVelocity, true, true);
	}
}

// Called every frame
void AChouCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AChouCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Movement actions
	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Movement actions
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AChouCharacter::Move);
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &AChouCharacter::Look);
		Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AChouCharacter::Jump);
	}

}

