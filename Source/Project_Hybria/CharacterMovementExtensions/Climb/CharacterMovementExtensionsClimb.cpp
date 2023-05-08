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

void UCharacterMovementExtensionsClimb::Tick(AProject_HybriaCharacter *Character)
{

    if (!IsValid(Character) || !IsValid(ClimbMontage))
        return;

    UCapsuleComponent *Capsule = Character->GetCapsuleComponent();

    if (!IsValid(Capsule))
        return;

    UCharacterMovementComponent *MovementComponent = Cast<UCharacterMovementComponent>(Character->GetMovementComponent());

    if (!IsValid(MovementComponent))
        return;

    USkeletalMeshComponent *SkeletalMeshComponent = Character->GetMesh();
    if (!IsValid(SkeletalMeshComponent))
        return;

    float HalfHeight = Capsule->GetScaledCapsuleHalfHeight();

    float Radius = 10.0f;

    ECollisionChannel TraceChannel = ECollisionChannel::ECC_GameTraceChannel1;
    bool bDebug = true;

    FVector Start = Character->GetActorLocation() + FVector(0, 0, HalfHeight + 20) + (Character->GetActorRotation().Vector() * 40); // tweak pour prendre en compte la position de la camera.
    FVector End = Start + FVector(0, 0, 10);


    bool bHit = SphereTraceByChannel::Trace(Character, Character->GetWorld(), Start, End, Radius, TraceChannel, EdgeHitResult, bDebug);
    
    if (bHit)
    {
        CapsuleComponent = Capsule;
        ActorComponent = Character;

        MovementComponent->StopMovementImmediately();
        Character->SetCanMoveAndState(true, ECharacterMovement::Clibing);
        MovementComponent->SetMovementMode(EMovementMode::MOVE_Flying);

        Start = Character->GetActorLocation();
        End = Start + (Character->GetActorRotation().Vector() * 80);


        FHitResult HitWallResult;
        bool bHitWall = SphereTraceByChannel::Trace(Character, Character->GetWorld(), Start, End, Radius, ECollisionChannel::ECC_WorldStatic, HitWallResult, bDebug);

        if ( bHitWall )
        {
            
            FVector XVector = HitWallResult.Normal * -1;
            FRotator NewRotation = Character->GetActorRotation();
            NewRotation.Yaw = UKismetMathLibrary::MakeRotFromX(XVector).Yaw;
            Character->SetActorRotation(NewRotation);


            auto Mesh = Character->GetMesh();

            if (!IsValid(Mesh))
                return;

            auto AnimInstance = Mesh->GetAnimInstance();

            if (!IsValid(AnimInstance))
                return;

            AnimInstance->Montage_Play(ClimbMontage, 1.0f);

            return;
        }
    }
    return;
}

void UCharacterMovementExtensionsClimb::FinishClimbing()
{         
    if (!IsValid(CapsuleComponent))
        return;

    if (!IsValid(ActorComponent))
        return;

    auto Mesh = ActorComponent->GetMesh();
                
    if (!IsValid(Mesh))
        return;

    auto AnimInstance = Mesh->GetAnimInstance();

    if (!IsValid(AnimInstance))
        return;

    AnimInstance->Montage_Pause(ClimbMontage);
    FLatentActionInfo Looll;
    Looll.CallbackTarget = this;
    Looll.ExecutionFunction = "JumbToFloor";
    Looll.Linkage = 0;
    Looll.UUID = GetNextUUID();
    auto HangLocation = FVector(ActorComponent->GetActorLocation().X, ActorComponent->GetActorLocation().Y, EdgeHitResult.Location.Z + HangZOffset);
    UE_LOG(LogTemp, Display, TEXT("%d"), HangZOffset);
    UE_LOG(LogTemp, Display, TEXT("%d"), HangAnimRate);
    UKismetSystemLibrary::MoveComponentTo(CapsuleComponent, HangLocation, ActorComponent->GetActorRotation(), false, false, HangAnimRate, false, EMoveComponentAction::Move, Looll);
}

void UCharacterMovementExtensionsClimb::JumbToFloor()
{
    if (!IsValid(CapsuleComponent))
        return;

    if (!IsValid(ActorComponent))
        return;

    auto Mesh = ActorComponent->GetMesh();
                
    if (!IsValid(Mesh))
        return;

    auto AnimInstance = Mesh->GetAnimInstance();

    if (!IsValid(AnimInstance))
        return;

    AnimInstance->Montage_Resume(ClimbMontage);

    float HalfHeight = CapsuleComponent->GetScaledCapsuleHalfHeight();

    auto HangHandOffsetCorrection = HangHandOffset < 0 ? HangHandOffset * -1 : HangHandOffset;
    auto ForwardVector = CapsuleComponent->GetForwardVector() * 10 * HangHandOffsetCorrection;
    auto UpVector = CapsuleComponent->GetUpVector() * HalfHeight * 3;
    FLatentActionInfo Looll;
    Looll.CallbackTarget = this;
    Looll.ExecutionFunction = "FreeMovement";
    Looll.Linkage = 0;
    Looll.UUID = GetNextUUID();
    UKismetSystemLibrary::MoveComponentTo(CapsuleComponent, ForwardVector + UpVector + ActorComponent->GetActorLocation(), ActorComponent->GetActorRotation(), false, false, ClimbAnimRate, false, EMoveComponentAction::Move, Looll);

}

void UCharacterMovementExtensionsClimb::FreeMovement()
{
    if (!IsValid(ActorComponent))
        return;   
    ActorComponent->SetCanMoveAndState(false, ECharacterMovement::Walk);
    UCharacterMovementComponent *MovementComponent = Cast<UCharacterMovementComponent>(ActorComponent->GetMovementComponent());
    MovementComponent->SetMovementMode(EMovementMode::MOVE_Walking);
}

int UCharacterMovementExtensionsClimb::GetNextUUID()
{
    return NextUUID++;
}