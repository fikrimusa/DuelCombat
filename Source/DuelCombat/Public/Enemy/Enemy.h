// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class DUELCOMBAT_API AEnemy : public ACharacter
{
	GENERATED_BODY()

	public:
		// Sets default values for this character's properties
		AEnemy();

		// Called every frame
		virtual void Tick(float DeltaTime) override;

	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

	private:	
		// base damage
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta = (AllowPrivateAccess = "true"))
		float BaseDamage;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta=(AllowPrivateAccess="true"))
		float Health;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
		float MaxHealth;

};
