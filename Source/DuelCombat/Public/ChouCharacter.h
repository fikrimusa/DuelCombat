// Fill out your copyright notice in the Description page of Project Settings.

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
	// Sets default values for this character's properties
	AChouCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Activate and deactivate weapon boxes
	virtual void ActivateRightWeapon();
	virtual void DeactivateRightWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="EnhancedInput")
	UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, Category="EnhancedInput")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputAction* BasicAttackAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputAction* HeavyAttackAction;


	//Movement
	void Move(const FInputActionValue& InputValue);
	void Look(const FInputActionValue& InputValue);
	void Jump();

	//Attack
	void BasicAttack();
	void HeavyAttack();

	void AnimMontagePlay(UAnimMontage* MontageToPlay, FName SectionName = "Default", float Playrate = 1.0f);

	// Right weapon overlap
	UFUNCTION()
	void OnRightWeaponOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess="true"))
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCameraComponent;

	// Montage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage", meta=(AllowPrivateAccess = "true"))
	UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* RightWeaponCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float BaseDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float MaxHealth;

};
