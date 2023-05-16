#include "BreathCircle.h"

#include "Components/Image.h"
#include "Components/Overlay.h"

UBreathCircle::UBreathCircle(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void UBreathCircle::SetValue(const float Value, const float DangerZoneBreathPercentage, const float MaxBreath, const FLinearColor BreathCircleColor, const FLinearColor BreathCircleColorDanger)
{
    if (IsValid(Material))
    {
        Material->SetScalarParameterValue("amount", Value);

        if (Value < MaxBreath * DangerZoneBreathPercentage)
        {
            Material->SetVectorParameterValue("color", BreathCircleColorDanger);
        }
        else
        {
            Material->SetVectorParameterValue("color", BreathCircleColor);
        }
    }
}
