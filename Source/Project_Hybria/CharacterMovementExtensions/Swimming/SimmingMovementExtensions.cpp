#include "SimmingMovementExtensions.h"
#include "../../Project_HybriaCharacter.h"
#include "../../HybriaLibrary/HybriaLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/CapsuleComponent.h"

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

    UKismetSystemLibrary::MoveComponentTo(Character->GetCapsuleComponent(), Location, Character->GetActorRotation(), false, false, 0.1, false, EMoveComponentAction::Move, Looll);
}