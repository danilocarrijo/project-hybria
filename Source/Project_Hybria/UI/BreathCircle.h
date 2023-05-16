#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BreathCircle.generated.h"

UCLASS()
class PROJECT_HYBRIA_API UBreathCircle : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UBreathCircle(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMaterialInstanceDynamic* Material;

	UFUNCTION(BlueprintCallable)
	void SetValue(float Value, float DangerZoneBreathPercentage, float MaxBreath, FLinearColor BreathCircleColor, FLinearColor BreathCircleColorDanger);
};