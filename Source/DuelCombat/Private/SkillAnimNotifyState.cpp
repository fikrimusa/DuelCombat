#include "SkillAnimNotifyState.h"

void USkillAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
    if (MeshComp && MeshComp->GetOwner())
    {
        ChouCharacter = Cast<AChouCharacter>(MeshComp->GetOwner());
        if (ChouCharacter)
        {
            if (bIsRightFist)
            {
                ChouCharacter->ActivateRightFist();
            }
            else
            {
                ChouCharacter->ActivateRightKick();
            }
        }
    }
}

void USkillAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    if (MeshComp && MeshComp->GetOwner())
    {
        if (ChouCharacter)
        {
            if (bIsRightFist)
            {
                ChouCharacter->DeactivateRightFist();
            }
            else
            {
                ChouCharacter->DeactivateRightKick();
            }
        }
    }
}
