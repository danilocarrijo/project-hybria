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

public:
    class UAnimMontage *MyMontage;

    UCharacterMovementExtensionsClimb();

    void Tick();

    UFUNCTION(BlueprintCallable)
    void JumbToFloor();

protected:

public:
    bool Tick(class AProject_HybriaCharacter *Character, class UWorld *Word);

    void FinishClimbing();
};