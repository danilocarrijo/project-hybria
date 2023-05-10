#pragma once

#include "CoreMinimal.h"
#include "SimmingMovementExtensions.generated.h"

UCLASS()
class USimmingMovementExtensions : public UObject
{
    GENERATED_BODY()
private:

public:
    void Tick(class AProject_HybriaCharacter *Character);

    float ZCorrection;

    bool CheckForWaterSurface(class AProject_HybriaCharacter *Character);

    void StartSwimming(class AProject_HybriaCharacter *Character);

protected:


};