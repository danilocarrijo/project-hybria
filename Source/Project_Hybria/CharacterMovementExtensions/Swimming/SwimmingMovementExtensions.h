#pragma once

#include "CoreMinimal.h"
#include "SwimmingMovementExtensions.generated.h"

UCLASS()
class PROJECT_HYBRIA_API USwimmingMovementExtensions : public UObject
{
    GENERATED_BODY()
private:

public:
    USwimmingMovementExtensions();
    
    void Tick(class AProject_HybriaCharacter *Character);

    float ZCorrection;

    bool CheckForWaterSurface(class AProject_HybriaCharacter *Character);

    void StartSwimming( class AProject_HybriaCharacter *Character);

    void StopSwimming();

    void GoToSurface(class AProject_HybriaCharacter *Character);

    UPROPERTY()
    class UNiagaraSystem* WaterRippleEffect;

    UPROPERTY()
    class UNiagaraSystem* WaterSplashEffect;

protected:
    UPROPERTY()
    class UNiagaraComponent* NiagaraComp;

    UPROPERTY()
    class UNiagaraComponent* NiagaraWaterSplash;

    FTimerHandle DestroyEffectTimerHandle;

    void DestroyEffect() const;

    float HitZLocation;

};