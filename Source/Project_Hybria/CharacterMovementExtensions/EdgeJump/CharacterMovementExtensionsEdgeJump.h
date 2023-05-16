#pragma once

#include "CoreMinimal.h"
#include "CharacterMovementExtensionsEdgeJump.generated.h"

UCLASS()
class PROJECT_HYBRIA_API UCharacterMovementExtensionsEdgeJump : public UObject
{
    GENERATED_BODY()
private:

public:
    UCharacterMovementExtensionsEdgeJump();
    
    static void Tick(class AProject_HybriaCharacter *Character);

protected:

};