#include "HybriaLibrary.h"
#include "Components/ShapeComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/PrimitiveComponent.h"


bool UHybriaLibrary::SphereTraceByChannel(AActor* Actor, UWorld* Word, FVector Start, FVector End, float Radius, ECollisionChannel TraceChannel, FHitResult& HitResult, bool bDebug)
{
    FCollisionQueryParams TraceParams(FName(TEXT("SphereTrace")), true, Actor);
    TraceParams.bTraceComplex = true;
    TraceParams.bReturnPhysicalMaterial = false;
    TraceParams.AddIgnoredActor(Actor);
    
    bool bHit = Word->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, TraceChannel, FCollisionShape::MakeSphere(Radius), TraceParams);
    
    if (bDebug)
    {
        DrawDebugSphere(Word, Start, Radius, 5, FColor::Green, false, 0.1f);
        DrawDebugSphere(Word, End, Radius, 5, FColor::Red, false, 0.1f);
		DrawDebugPoint(Word, HitResult.ImpactPoint, 10.0f, FColor::Blue, false, 1.0f);
    }
    
	return bHit;
}