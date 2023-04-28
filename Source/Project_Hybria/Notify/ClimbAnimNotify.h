// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "ClimbAnimNotify.generated.h"

/**
 *
 */
UCLASS()
class PROJECT_HYBRIA_API UClimbAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation);
};
