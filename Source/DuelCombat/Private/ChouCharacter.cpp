// Developed by Fikri

#include "ChouCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Layers/LayersSubsystem.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ChouAnimInstance.h"
#include "HitInterface.h"
#include <Kismet/GameplayStatics.h>

// Sets default values for this character's properties
AChouCharacter::AChouCharacter() :
	BaseDamage(20.f) // Initialize Base Damage
{
	// Set this character to call Tick() every frame. Disable it if unnecessary for performance.
	PrimaryActorTick.bCanEverTick = true;

	// Set up the camera boom (SpringArm) for third-person view
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 400.f; // Set distance of the camera from character
	SpringArmComponent->bUsePawnControlRotation = true; // Allow camera to rotate with player control

	// Set up the follow camera
	FollowCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	FollowCameraComponent->bUsePawnControlRotation = false; // Prevent camera rotation from pawn

	// Jump settings for movement
	GetCharacterMovement()->JumpZVelocity = 300.f; // Vertical speed for jump
	GetCharacterMovement()->AirControl = 0.1f; // Control when in the air

	// Right fist collision box setup
	RightFistCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("FistAction"));
	RightFistCollisionBox->SetupAttachment(RootComponent);
	RightFistCollisionBox->SetHiddenInGame(false);

	// Right kick collision box setup
	RightKickCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("KickAction"));
	RightKickCollisionBox->SetupAttachment(RootComponent);
	RightKickCollisionBox->SetHiddenInGame(false);
}

// Called when the game starts or when spawned
void AChouCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Add input mapping context for enhanced input system
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapping, 0); // Add input context
		}
	}

	const FAttachmentTransformRules AttachmentRules1(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);
	RightFistCollisionBox->AttachToComponent(GetMesh(), AttachmentRules1, "FistCollision");

	RightFistCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AChouCharacter::OnRightWeaponOverlap);
	
	RightFistCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightFistCollisionBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	RightFistCollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	RightFistCollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);


	const FAttachmentTransformRules AttachmentRules2(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);
	RightKickCollisionBox->AttachToComponent(GetMesh(), AttachmentRules2, "KickCollision");

	RightKickCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AChouCharacter::OnRightWeaponOverlap);

	RightKickCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightKickCollisionBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	RightKickCollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	RightKickCollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

// Handle player movement input (forward/backward/side-to-side)
void AChouCharacter::Move(const FInputActionValue& InputValue)
{
	FVector2d InputVector = InputValue.Get<FVector2d>();

	if (IsValid(Controller))
	{
		// Get forward direction from controller's control rotation
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0); // Use only yaw for movement direction

		// Get unit direction vectors for forward and right movement
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Add movement input based on the player's input values
		AddMovementInput(ForwardDirection, InputVector.Y);
		AddMovementInput(RightDirection, InputVector.X);
	}
}

// Handle player looking around input (camera rotation)
void AChouCharacter::Look(const FInputActionValue& InputValue)
{
	FVector2d InputVector = InputValue.Get<FVector2d>();

	if (IsValid(Controller))
	{
		AddControllerYawInput(InputVector.X); // Yaw rotation (turning)
		AddControllerPitchInput(InputVector.Y); // Pitch rotation (looking up/down)
	}
}

// Override jump behavior to combine forward velocity with upward velocity
void AChouCharacter::Jump()
{
	Super::Jump(); // Call base class Jump()

	if (GetCharacterMovement()->IsMovingOnGround())
	{
		// Get current forward velocity and adjust vertical velocity for jumping
		FVector ForwardVelocity = GetVelocity();
		ForwardVelocity.Z = 0; // Zero out Z-axis for horizontal velocity
		float JumpVerticalVelocity = GetCharacterMovement()->JumpZVelocity;

		// Launch character with combined forward and vertical velocities
		FVector JumpVelocity = ForwardVelocity + FVector(0, 0, JumpVerticalVelocity);
		LaunchCharacter(JumpVelocity, true, true);
	}
}

// Basic attack: Play animation for basic attack
void AChouCharacter::BasicAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Basic Attack"));
	AnimMontagePlay(AttackMontage, FName("Attack1"));
}

// Heavy attack: Play animation for heavy attack
void AChouCharacter::HeavyAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Heavy Attack"));
	AnimMontagePlay(AttackMontage, FName("Attack2"), 2.f);
}

// Play animation montage, checking if it is already playing to avoid overlap
void AChouCharacter::AnimMontagePlay(UAnimMontage* MontageToPlay, FName SectionName, float Playrate)
{
	UChouAnimInstance* AnimInstance = Cast<UChouAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance && MontageToPlay)
	{
		if (!AnimInstance->Montage_IsPlaying(MontageToPlay)) // Avoid playing the same montage multiple times
		{
			PlayAnimMontage(MontageToPlay, Playrate, SectionName);
		}
	}
}

// Handle weapon collision overlap and apply damage if valid target is hit
void AChouCharacter::OnRightWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(SweepResult.GetActor()) && SweepResult.GetActor() != this)
	{
		IHitInterface* HitInterface = Cast<IHitInterface>(SweepResult.GetActor());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Apply Damage"));
		if (HitInterface)
		{
			HitInterface->HitInterface_Implementation(SweepResult);
		}

		UGameplayStatics::ApplyDamage(
			SweepResult.GetActor(),
			BaseDamage,
			GetController(),
			this,
			UDamageType::StaticClass());
	}

}

// Called every frame to update character state
void AChouCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Bind input actions to corresponding functions (e.g., movement, attacks)
void AChouCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Movement actions
	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Bind movement input actions to corresponding functions
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AChouCharacter::Move);
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &AChouCharacter::Look);
		Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AChouCharacter::Jump);

		// Bind attack input actions to corresponding functions
		Input->BindAction(BasicAttackAction, ETriggerEvent::Triggered, this, &AChouCharacter::BasicAttack);
		Input->BindAction(HeavyAttackAction, ETriggerEvent::Triggered, this, &AChouCharacter::HeavyAttack);
	}
}

void AChouCharacter::ActivateRightFist()
{
	RightFistCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AChouCharacter::DeactivateRightFist()
{
	RightFistCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AChouCharacter::ActivateRightKick()
{
	RightKickCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AChouCharacter::DeactivateRightKick()
{
	RightKickCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
