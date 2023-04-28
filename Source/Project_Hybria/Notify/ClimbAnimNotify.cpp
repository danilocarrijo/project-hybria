// Fill out your copyright notice in the Description page of Project Settings.


#include "ClimbAnimNotify.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/LatentActionManager.h"
#include "Engine.h"

void UClimbAnimNotify::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
    GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Green, __FUNCTION__);
    UAnimInstance* AnimInstance = MeshComp->GetAnimInstance();
    UAnimMontage* Montage = AnimInstance->GetCurrentActiveMontage();
    AnimInstance->Montage_Stop(0.2f, Montage);
}