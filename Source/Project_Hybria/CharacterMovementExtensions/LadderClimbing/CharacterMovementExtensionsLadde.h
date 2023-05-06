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

    void SetLadderProperties(float OffSet, float BottomDistanceToDrop);

	bool DropBottom(class AProject_HybriaCharacter *Character);

protected:
	float Direction;

	FVector LadderBottom;
	
	FVector LadderTop;

	float OffSet;

	float BottomDistanceToDrop;

	float GetBottomDistance(class AProject_HybriaCharacter *Character);

};