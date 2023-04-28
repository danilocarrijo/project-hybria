
#include "CoreMinimal.h"

class SphereTraceByChannel
{
private:

public:
    static bool Trace(AActor* Actor, UWorld* Word, FVector Start, FVector End, float Radius, ECollisionChannel TraceChannel, FHitResult& HitResult, bool bDebug);
};