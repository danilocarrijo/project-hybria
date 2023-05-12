#include "SimmingMovementExtensions.h"
#include "../../Project_HybriaCharacter.h"
#include "../../HybriaLibrary/HybriaLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/CapsuleComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"

void USimmingMovementExtensions::Tick(AProject_HybriaCharacter *Character)
{
}

bool USimmingMovementExtensions::CheckForWaterSurface(class AProject_HybriaCharacter *Character)
{
    bool bDebug = true;
    UCapsuleComponent *Capsule = Character->GetCapsuleComponent();

    float HalfHeight = Capsule->GetScaledCapsuleHalfHeight();

    FVector Start = Character->GetActorLocation() + Character->GetActorForwardVector() * 2;
    FVector End = Start - FVector(0, 0, HalfHeight + 10);
    FHitResult Hit;


    return UHybriaLibrary::SphereTraceByChannel(Character, Character->GetWorld(), Start, End, 10.0f, ECollisionChannel::ECC_GameTraceChannel2, Hit, bDebug);
    
}

void USimmingMovementExtensions::StartSwimming(AProject_HybriaCharacter *Character)
{

	if(!IsValid(Character)) return;

    UCapsuleComponent *Capsule = Character->GetCapsuleComponent();

    if (!IsValid(Capsule))
        return;

    Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);

    float HalfHeight = Capsule->GetScaledCapsuleHalfHeight();

    FVector Location = FVector(Character->GetActorLocation().X, Character->GetActorLocation().Y, Character->GetActorLocation().Z - HalfHeight + ZCorrection);
    FLatentActionInfo Looll;

	Looll.CallbackTarget = this;    
    if (WaterSplashEffect)
    {
        NiagaraWaterSplash = UNiagaraFunctionLibrary::SpawnSystemAttached(WaterSplashEffect, Character->GetRootComponent(), NAME_None, FVector(0.f), FRotator(0.f), EAttachLocation::Type::KeepRelativeOffset, true);

        Character->GetWorldTimerManager().SetTimer(DestroyEffectTimerHandle, this, &USimmingMovementExtensions::DestroyEffect, 3.0f, false);
    }

    UKismetSystemLibrary::MoveComponentTo(Character->GetCapsuleComponent(), Location, Character->GetActorRotation(), false, false, 0.1, false, EMoveComponentAction::Move, Looll);

    if (WaterRippleEffect)
    {
        NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(WaterRippleEffect, Character->GetRootComponent(), NAME_None, FVector(0.f), FRotator(0.f), EAttachLocation::Type::KeepRelativeOffset, true);
    }
}

void USimmingMovementExtensions::DestroyEffect()
{
  if (NiagaraWaterSplash)
    {
        NiagaraWaterSplash->DestroyComponent();
    }  
}

void USimmingMovementExtensions::StotSwimming()
{
  if (NiagaraComp)
    {
        NiagaraComp->DestroyComponent();
    }  
}