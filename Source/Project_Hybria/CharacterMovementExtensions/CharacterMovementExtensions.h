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

public:
    UCharacterMovementExtensions();
    
    void Tick(class AProject_HybriaCharacter *Character);

public:
	ECharacterMovement CurrMovement = ECharacterMovement::Walk;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MyActor")
        bool bLockMoviment = false;

    void ClimbEvent(class UAnimMontage* ClimbMontage, float HangAnimRate, float ClimbAnimRate, int HangHandOffset, int HangZOffset);

    void EdgeJumpEvent();

    void FinishClimbing();
};