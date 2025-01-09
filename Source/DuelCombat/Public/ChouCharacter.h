// Developed by Fikri

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Components/BoxComponent.h"
#include "ChouCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UAnimMontage;

UCLASS()
class DUELCOMBAT_API AChouCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Default constructor for AChouCharacter. Sets default values for character properties.
	AChouCharacter();

	// Called every frame to update character's state.
	virtual void Tick(float DeltaTime) override;

	// Binds input actions to the player input component.
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Activates the right weapon's hitbox or collision component.
	virtual void ActivateRightWeapon();

	// Deactivates the right weapon's hitbox or collision component.
	virtual void DeactivateRightWeapon();

protected:
	// Called when the game starts or when the character is spawned in the game world.
	virtual void BeginPlay() override;

	// Input mapping for enhanced input system. Associates input actions to gameplay actions.
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputMappingContext* InputMapping;

	// Action for moving the character.
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputAction* MoveAction;

	// Action for looking (camera control).
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputAction* LookAction;

	// Action for jumping.
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputAction* JumpAction;

	// Action for basic attack input.
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputAction* BasicAttackAction;

	// Action for heavy attack input.
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputAction* HeavyAttackAction;

	// Movement functions called based on player input.
	void Move(const FInputActionValue& InputValue);

	// Camera look (mouse or analog stick input).
	void Look(const FInputActionValue& InputValue);

	// Executes jump action.
	void Jump();

	// Executes basic attack functionality.
	void BasicAttack();

	// Executes heavy attack functionality.
	void HeavyAttack();

	// Plays an animation montage for combat actions.
	void AnimMontagePlay(UAnimMontage* MontageToPlay, FName SectionName = "Default", float Playrate = 1.0f);

	// Handles the overlap event for the right weapon's collision box.
	UFUNCTION()
	void OnRightWeaponOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

private:
	// Camera system for following the character's movement.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;

	// Camera component that provides the player's view of the game world.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCameraComponent;

	// Animation montage for combat-related actions (attacks, etc.).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AttackMontage;

	// Collision box for detecting right weapon hits.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* RightWeaponCollisionBox;

	// Base damage value applied by the character's attacks.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float BaseDamage;

	// Current health of the character.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float Health;

	// Maximum health of the character.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float MaxHealth;
};
