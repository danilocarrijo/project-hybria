#pragma once

#include "CoreMinimal.h"
#include "../CharacterMovement.h"
#include "Climb/CharacterMovementExtensionsClimb.h"
#include "CharacterMovementExtensions.generated.h"

UCLASS()
class UCharacterMovementExtensions: public UObject
{
    GENERATED_BODY()
private:
    class UCharacterMovementExtensionsClimb* ClimbExtensions;
    class UCharacterMovementExtensionsEdgeJump* EdgeJumpExtensions;
    class UCharacterMovementExtensionsLadde* LadderClimbingExtensions;

	void MoveForwardWalk(float Value, AProject_HybriaCharacter *Character);

	void MoveRightWalk(float Value, AProject_HybriaCharacter *Character);

    void MoveForwardLadder(float Value, AProject_HybriaCharacter *Character);

public:
    UCharacterMovementExtensions();
    
    void Tick(class AProject_HybriaCharacter *Character);

public:
	ECharacterMovement CurrMovement = ECharacterMovement::Walk;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MyActor")
        bool bLockMoviment = false;

    void Init(class AProject_HybriaCharacter *Character);

    void ChangeState(bool bLockMoviment, ECharacterMovement Movement, AProject_HybriaCharacter *Character);

    void FinishClimbing();

    void Jump(AProject_HybriaCharacter *Character);

	/** Called for forwards/backward input */
	void MoveForward(float Value, AProject_HybriaCharacter *Character);

	/** Called for side to side input */
	void MoveRight(float Value, AProject_HybriaCharacter *Character);

    void StartClimbingLadder(class AProject_HybriaCharacter *Character, class ALadder *Ladder, float ZCorrection, float OffSet, float BottomDistanceToDrop);

    void StopClimbingLadder();

	float GetClimbingLadderDirection();
};