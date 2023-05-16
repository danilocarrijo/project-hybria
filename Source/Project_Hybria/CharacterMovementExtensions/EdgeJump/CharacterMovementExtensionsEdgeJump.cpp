#include "CharacterMovementExtensionsEdgeJump.h"
#include "../../Project_HybriaCharacter.h"
#include "../../HybriaLibrary/HybriaLibrary.h"
#include "Components/CapsuleComponent.h"

UCharacterMovementExtensionsEdgeJump::UCharacterMovementExtensionsEdgeJump()
{
}

void UCharacterMovementExtensionsEdgeJump::Tick(AProject_HybriaCharacter *Character)
{
    constexpr bool bDebug = true;
    const UCapsuleComponent *Capsule = Character->GetCapsuleComponent();

    const float HalfHeight = Capsule->GetScaledCapsuleHalfHeight();

    const FVector Start = Character->GetActorLocation() + Character->GetActorForwardVector() * 2;
    const FVector End = Start - FVector(0, 0, HalfHeight + 10);
    FHitResult Hit;


    if (const bool bHit = UHybriaLibrary::SphereTraceByChannel(Character, Character->GetWorld(), Start, End, 10.0f, ECollisionChannel::ECC_WorldStatic, Hit, bDebug); !bHit)
    {
        Character->Jump();

    }
}
