#pragma once

#include "CoreMinimal.h"
#include "CharacterMovementExtensionsClimb.generated.h"

UCLASS()
class UCharacterMovementExtensionsClimb : public UObject
{
    GENERATED_BODY()
private:
    class UCapsuleComponent *CapsuleComponent;
    class AProject_HybriaCharacter *ActorComponent;
    FHitResult EdgeHitResult;
    int32 NextUUID = 0;

    int GetNextUUID();

public:
    UCharacterMovementExtensionsClimb();

    UFUNCTION(BlueprintCallable)
    void JumbToFloor();

    UFUNCTION(BlueprintCallable)
    void FreeMovement();

    UFUNCTION(BlueprintCallable)
    void SetCanWalkAndFinish();

protected:

public:
    bool Tick(class AProject_HybriaCharacter *Character);

    void FinishClimbing();

    float HangAnimRate;

    float ClimbAnimRate;

    int HangHandOffset;

    int HangZOffset;

    class UAnimMontage* ClimbMontage;
};