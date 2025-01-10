// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChouCharacter.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "SkillAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class DUELCOMBAT_API USkillAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Type")
	bool bIsRightFist; // Set to true for fist, false for kick

	UPROPERTY()
	AChouCharacter* ChouCharacter;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
};
