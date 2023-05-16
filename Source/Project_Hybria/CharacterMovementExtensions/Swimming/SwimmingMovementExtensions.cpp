#include "SwimmingMovementExtensions.h"
#include "../../Project_HybriaCharacter.h"
#include "../../HybriaLibrary/HybriaLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/CapsuleComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"

USwimmingMovementExtensions::USwimmingMovementExtensions()
{
}

void USwimmingMovementExtensions::Tick(AProject_HybriaCharacter *Character)
{
}

bool USwimmingMovementExtensions::CheckForWaterSurface(AProject_HybriaCharacter *Character)
{
    constexpr bool bDebug = true;
    const UCapsuleComponent *Capsule = Character->GetCapsuleComponent();

    const float HalfHeight = Capsule->GetScaledCapsuleHalfHeight();

    const FVector Start = Character->GetActorLocation() + Character->GetActorForwardVector() * 2;
    const FVector End = Start - FVector(0, 0, HalfHeight + 10);

    if (FHitResult Hit; UHybriaLibrary::SphereTraceByChannel(Character, Character->GetWorld(), Start, End, 10.0f, ECollisionChannel::ECC_GameTraceChannel2, Hit, bDebug))
    {
        HitZLocation = Hit.Location.Z;
        return true;
    }
    return false;
    
}

void USwimmingMovementExtensions::StartSwimming(AProject_HybriaCharacter *Character)
{

    if(!IsValid(Character)) return;

    const UCapsuleComponent *Capsule = Character->GetCapsuleComponent();
    
    if (!IsValid(Capsule))
        return;

    const float HalfHeight = Capsule->GetScaledCapsuleHalfHeight();

    const FVector Location = FVector(Character->GetActorLocation().X, Character->GetActorLocation().Y, HitZLocation - HalfHeight + ZCorrection);
    FLatentActionInfo Looll;

    Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("A distância entre os pontos")));
    if (WaterSplashEffect)
    {
        NiagaraWaterSplash = UNiagaraFunctionLibrary::SpawnSystemAttached(WaterSplashEffect, Character->GetRootComponent(), NAME_None, FVector(0.f), FRotator(0.f), EAttachLocation::Type::KeepRelativeOffset, true);

        Character->GetWorldTimerManager().SetTimer(DestroyEffectTimerHandle, this, &USwimmingMovementExtensions::DestroyEffect, 3.0f, false);
    }
    Character->SetActorLocation(Location);

    if (WaterRippleEffect)
    {
        NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(WaterRippleEffect, Character->GetRootComponent(), NAME_None, FVector(0.f), FRotator(0.f), EAttachLocation::Type::KeepRelativeOffset, true);
    }
    
}

void USwimmingMovementExtensions::DestroyEffect() const
{
  if (NiagaraWaterSplash)
    {
        NiagaraWaterSplash->DestroyComponent();
    }  
}

void USwimmingMovementExtensions::StopSwimming()
{
  if (NiagaraComp)
    {
        NiagaraComp->DestroyComponent();
    }  
}

void USwimmingMovementExtensions::GoToSurface(AProject_HybriaCharacter* Character)
{
    if(!IsValid(Character)) return;

    const UCapsuleComponent *Capsule = Character->GetCapsuleComponent();
    
    if (!IsValid(Capsule))
        return;

    const float HalfHeight = Capsule->GetScaledCapsuleHalfHeight();

    const FVector Location = FVector(Character->GetActorLocation().X, Character->GetActorLocation().Y, HitZLocation - HalfHeight + ZCorrection);
    FLatentActionInfo Looll;
    Looll.CallbackTarget = this;
    Looll.Linkage = 0;
    UKismetSystemLibrary::MoveComponentTo(Character->GetCapsuleComponent(), Location, Character->GetActorRotation(), false, false, 0.1f, false, EMoveComponentAction::Move, Looll);
    
    if (WaterRippleEffect)
    {
        NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(WaterRippleEffect, Character->GetRootComponent(), NAME_None, FVector(0.f), FRotator(0.f), EAttachLocation::Type::KeepRelativeOffset, true);
    }
}
