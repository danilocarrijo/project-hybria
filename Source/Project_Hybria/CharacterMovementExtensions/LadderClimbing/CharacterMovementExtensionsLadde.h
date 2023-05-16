// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterMovementExtensionsLadde.generated.h"

UCLASS()
class PROJECT_HYBRIA_API UCharacterMovementExtensionsLadde : public UObject
{
    GENERATED_BODY()

public:
	
	UCharacterMovementExtensionsLadde() {}
	
	void Climb(float Value, class AProject_HybriaCharacter *Character);

	float LadderClimbSpeed;

    void StopClimbingLadder();

    void StartClimbingLadder(class AProject_HybriaCharacter *Character, class ALadder *Ladder, float ZCorrection);

	float GetDirection() const;

    void SetLadderProperties(float OffSet, float BottomDistanceToDrop, float TopDistanceToClimb, class UAnimMontage* EdgeJumpingClimbMontage);

	bool DropBottom(class AProject_HybriaCharacter *Character);

	bool ClimbUp(const AProject_HybriaCharacter *Character) const;

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

	float GetBottomDistance(const class AProject_HybriaCharacter *Character) const;

	float GetTopDistance(const class AProject_HybriaCharacter *Character) const;

	void FinishClimbUp(const class AProject_HybriaCharacter *Character) const;

	UPROPERTY()
	class UAnimMontage* EdgeJumpingClimbMontage;

	UPROPERTY()
    class AProject_HybriaCharacter *ActorComponent;

	bool bCanClimb = true;

};