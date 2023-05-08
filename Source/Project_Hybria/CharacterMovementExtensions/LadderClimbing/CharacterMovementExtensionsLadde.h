// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterMovementExtensionsLadde.generated.h"

UCLASS()
class UCharacterMovementExtensionsLadde : public UObject
{
    GENERATED_BODY()
private:

public:
	void Climb(float Value, class AProject_HybriaCharacter *Character);

	float LadderClimbSpeed;

    void StopClimbingLadder();

    void StartClimbingLadder(class AProject_HybriaCharacter *Character, class ALadder *Ladder, float ZCorrection);

	float GetDirection();

    void SetLadderProperties(float OffSet, float BottomDistanceToDrop, float TopDistanceToClimb, class UAnimMontage* EdgeJumpingClimbMontage);

	bool DropBottom(class AProject_HybriaCharacter *Character);

	bool ClimbUp(AProject_HybriaCharacter *Character);

    UFUNCTION(BlueprintCallable)
    void FreeMovement();

	void FinishLadderClimbing(class AProject_HybriaCharacter *Character);

protected:
	float Direction;

	FVector LadderBottom;
	
	FVector LadderTop;

	float OffSet;

	float BottomDistanceToDrop;

	float TopDistanceToClimb;

	float GetBottomDistance(class AProject_HybriaCharacter *Character);

	float GetTopDistance(class AProject_HybriaCharacter *Character);

	void FinishClimbUp(class AProject_HybriaCharacter *Character);

	class UAnimMontage* EdgeJumpingClimbMontage;

    class AProject_HybriaCharacter *ActorComponent;

	bool bCanClimb = true;

};