#pragma once

#include "CoreMinimal.h"
#include "DivingMovementExtensions.generated.h"

UCLASS()
class PROJECT_HYBRIA_API UDivingMovementExtensions : public UObject
{
    GENERATED_BODY()
private:
    int DivingDirection = -1;

    bool CheckForBottom(class AProject_HybriaCharacter *Character) const;

    bool CheckForTop(class AProject_HybriaCharacter *Character) const;
    
    float CurrBreath;

    float TickTime = 0.0f;
    
public:
    UDivingMovementExtensions();
    
    void Tick(float DeltaTime, class AProject_HybriaCharacter *Character);

    void StartDiving(class AProject_HybriaCharacter *Character);

    void StopDiving(class AProject_HybriaCharacter *Character);

    int GetDivingDirection() const;
    
    float GetCurrBreath() const;

    float DiveSpeed;
    
    float DiveBottomHitTolerance;
    
    float DiveTopHitTolerance;
    
    float MaxBreath;
    
    float DangerZoneBreathPercentage;
    
    float UnderwaterTimeCount;
    
    FLinearColor BreathCircleColor;
    
    FLinearColor BreathCircleColorDanger;

protected:

};