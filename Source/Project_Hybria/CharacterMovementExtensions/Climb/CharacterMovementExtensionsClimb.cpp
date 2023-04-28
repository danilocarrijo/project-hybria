#include "CharacterMovementExtensionsClimb.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "../CharacterMovementExtensions.h"
#include "../../Project_HybriaCharacter.h"
#include "../../Helpers/SphereTraceByChannel.h"
#include "Engine/World.h"

UCharacterMovementExtensionsClimb::UCharacterMovementExtensionsClimb()
{
}

bool UCharacterMovementExtensionsClimb::Tick(AProject_HybriaCharacter *Character, UWorld *Word)
{

    if (Character == nullptr || MyMontage == nullptr)
        return false;

    UCapsuleComponent *Capsule = Character->GetCapsuleComponent();
    UCharacterMovementComponent *MovementComponent = Cast<UCharacterMovementComponent>(Character->GetMovementComponent());
    USkeletalMeshComponent *SkeletalMeshComponent = Character->GetMesh();

    float HalfHeight = Capsule->GetScaledCapsuleHalfHeight();

    float Radius = 10.0f;

    ECollisionChannel TraceChannel = ECollisionChannel::ECC_GameTraceChannel1;
    bool bDebug = true;

    FVector Start = Character->GetActorLocation() + FVector(0, 0, HalfHeight + 20) + (Character->GetActorRotation().Vector() * 40); // tweak pour prendre en compte la position de la camera.
    FVector End = Start + FVector(0, 0, 10);


    bool bHit = SphereTraceByChannel::Trace(Character, Word, Start, End, Radius, TraceChannel, EdgeHitResult, bDebug);
    
    if (bHit)
    {
        CapsuleComponent = Capsule;
        ActorComponent = Character;

        MovementComponent->StopMovementImmediately();
        ActorComponent->SetCanMoveAndState(true, ECharacterMovement::Clibing);
        MovementComponent->SetMovementMode(EMovementMode::MOVE_Flying);

        Start = Character->GetActorLocation();
        End = Start + (Character->GetActorRotation().Vector() * 80);


        FHitResult HitWallResult;
        bool bHitWall = SphereTraceByChannel::Trace(Character, Word, Start, End, Radius, ECollisionChannel::ECC_WorldStatic, HitWallResult, bDebug);

        if ( bHitWall )
        {
            
            FVector XVector = HitWallResult.Normal * -1;
            FRotator NewRotation = Character->GetActorRotation();
            NewRotation.Yaw = UKismetMathLibrary::MakeRotFromX(XVector).Yaw;
            Character->SetActorRotation(NewRotation);


            if (MyMontage != nullptr)
            { 

                ActorComponent->GetMesh()->GetAnimInstance()->Montage_Play(MyMontage, 1.0f);

                return true;
            }
        }
    }
    return false;
}

void UCharacterMovementExtensionsClimb::FinishClimbing()
{
    ActorComponent->GetMesh()->GetAnimInstance()->Montage_Pause(MyMontage);
    FLatentActionInfo Looll;
    Looll.CallbackTarget = this;
    Looll.ExecutionFunction = "JumbToFloor";
    Looll.Linkage = 0;
    UKismetSystemLibrary::MoveComponentTo(CapsuleComponent, EdgeHitResult.Location, ActorComponent->GetActorRotation(), false, false, 0.5f, false, EMoveComponentAction::Move, Looll);
}

void UCharacterMovementExtensionsClimb::JumbToFloor()
{
    ActorComponent->GetMesh()->GetAnimInstance()->Montage_Resume(MyMontage);

    float HalfHeight = CapsuleComponent->GetScaledCapsuleHalfHeight();
    UCharacterMovementComponent *MovementComponent = Cast<UCharacterMovementComponent>(ActorComponent->GetMovementComponent());

    auto ForwardVector = CapsuleComponent->GetForwardVector() * 50;
    auto UpVector = CapsuleComponent->GetUpVector() * HalfHeight * 2;
    FLatentActionInfo Looll;
    Looll.CallbackTarget = this;
    UKismetSystemLibrary::MoveComponentTo(CapsuleComponent, ForwardVector + UpVector + ActorComponent->GetActorLocation(), ActorComponent->GetActorRotation(), false, false, 0.5f, false, EMoveComponentAction::Move, Looll);
    ActorComponent->SetCanMoveAndState(false, ECharacterMovement::Walk);
    MovementComponent->SetMovementMode(EMovementMode::MOVE_Walking);
}