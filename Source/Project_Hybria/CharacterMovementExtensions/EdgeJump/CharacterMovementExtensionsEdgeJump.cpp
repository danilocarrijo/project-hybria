#include "CharacterMovementExtensionsEdgeJump.h"
#include "../../Project_HybriaCharacter.h"
#include "../../HybriaLibrary/HybriaLibrary.h"
#include "Components/CapsuleComponent.h"

void UCharacterMovementExtensionsEdgeJump::Tick(AProject_HybriaCharacter *Character)
{
    bool bDebug = true;
    UCapsuleComponent *Capsule = Character->GetCapsuleComponent();

    float HalfHeight = Capsule->GetScaledCapsuleHalfHeight();

    FVector Start = Character->GetActorLocation() + Character->GetActorForwardVector() * 2;
    FVector End = Start - FVector(0, 0, HalfHeight + 10);
    FHitResult Hit;


    bool bHit = UHybriaLibrary::SphereTraceByChannel(Character, Character->GetWorld(), Start, End, 10.0f, ECollisionChannel::ECC_WorldStatic, Hit, bDebug);

    if (!bHit)
    {
        Character->Jump();

    }
}