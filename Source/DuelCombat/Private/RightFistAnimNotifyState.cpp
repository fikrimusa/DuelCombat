// Fill out your copyright notice in the Description page of Project Settings.


#include "RightFistAnimNotifyState.h"

void URightFistAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		ChouCharacter = Cast<AChouCharacter>(MeshComp->GetOwner());
		if (ChouCharacter)
		{
			ChouCharacter->ActivateRightWeapon();
		}
	}
}

void URightFistAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ChouCharacter)
		{
			ChouCharacter->DeactivateRightWeapon();
		}
	}
}
