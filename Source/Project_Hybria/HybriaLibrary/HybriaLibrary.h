
#pragma once

#include "CoreMinimal.h"
#include "HybriaLibrary.generated.h"

UCLASS()
class PROJECT_HYBRIA_API UHybriaLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    static bool SphereTraceByChannel(AActor* Actor, UWorld* Word, FVector Start, FVector End, float Radius, ECollisionChannel TraceChannel, FHitResult& HitResult, bool bDebug);
};