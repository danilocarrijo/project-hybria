#include "CharacterMovementExtensionsLadde.h"
#include "../../Project_HybriaCharacter.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/Engine.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../../Ladder.h"

bool UCharacterMovementExtensionsLadde::DropBottom(AProject_HybriaCharacter *Character)
{
    float Distance = GetBottomDistance(Character);

    return Distance < BottomDistanceToDrop;
}

bool UCharacterMovementExtensionsLadde::ClimbUp(AProject_HybriaCharacter *Character)
{
    float Distance = GetTopDistance(Character);

    return Distance < TopDistanceToClimb;
}

float UCharacterMovementExtensionsLadde::GetBottomDistance(AProject_HybriaCharacter *Character)
{
    FVector ActorLocation = Character->GetCapsuleComponent()->GetComponentLocation();

    float Distance = ActorLocation.Z - LadderBottom.Z;
    Distance = FMath::Abs(Distance);

    return Distance;
}

float UCharacterMovementExtensionsLadde::GetTopDistance(AProject_HybriaCharacter *Character)
{
    FVector ActorLocation = Character->GetCapsuleComponent()->GetComponentLocation();

    float Distance = ActorLocation.Z - LadderTop.Z;
    Distance = FMath::Abs(Distance);

    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("A distância entre os pontos é %f"), Distance));

    return Distance;
}

void UCharacterMovementExtensionsLadde::Climb(float Value, AProject_HybriaCharacter *Character)
{
    if (!bCanClimb) return;

    auto bDrop = DropBottom(Character);
    auto bClimbUp = ClimbUp(Character);

    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("A distância entre os pontos é %d"), bDrop));

    if (bDrop)
    {
        Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
        Character->SetCanMoveAndState(false, ECharacterMovement::Walk);
        StopClimbingLadder();
        return;
    }

    if (bClimbUp)
    {
        StopClimbingLadder();
        FinishClimbUp(Character);
        bCanClimb = false;
        return;
    }

    
    Direction = Value;

    const FVector UpVector = FVector(0.0f, 0.0f, 1.0f * Value * LadderClimbSpeed);
    // Adiciona a força do vetor de direção calculado para subir as escadas ou para baixo, dependendo do valor de entrada
    const FVector NewLocation = Character->GetActorLocation() + UpVector;
    // Move o componente de movimento do personagem para a nova posição
    Character->GetCharacterMovement()->MoveUpdatedComponent(UpVector, Character->GetActorRotation(), true);
    // Define a nova posição do personagem
    Character->SetActorLocation(NewLocation);
}

void UCharacterMovementExtensionsLadde::StopClimbingLadder()
{
    Direction = 0;
}

void UCharacterMovementExtensionsLadde::FinishClimbUp(AProject_HybriaCharacter *Character)
{
   auto Mesh = Character->GetMesh();
                
    if (!IsValid(Mesh))
        return;

    auto AnimInstance = Mesh->GetAnimInstance();

    if (!IsValid(AnimInstance))
        return;

    AnimInstance->Montage_Play(EdgeJumpingClimbMontage, 1.0f);
}

void UCharacterMovementExtensionsLadde::FinishLadderClimbing(AProject_HybriaCharacter *Character)
{
    if (!IsValid(Character))
        return;

    auto CapsuleComponent = Character->GetCapsuleComponent();

    if (!IsValid(CapsuleComponent))
        return;

    float HalfHeight = CapsuleComponent->GetScaledCapsuleHalfHeight();

    ActorComponent = Character;

    auto ForwardVector = CapsuleComponent->GetForwardVector() * 100;
    auto UpVector = CapsuleComponent->GetUpVector() * HalfHeight * 2;
    FLatentActionInfo Looll;
    Looll.CallbackTarget = this;
    Looll.ExecutionFunction = "FreeMovement";
    Looll.Linkage = 0;
    UKismetSystemLibrary::MoveComponentTo(CapsuleComponent, ForwardVector + UpVector + Character->GetActorLocation(), Character->GetActorRotation(), false, false, 0.2f, false, EMoveComponentAction::Move, Looll);
}

void UCharacterMovementExtensionsLadde::FreeMovement()
{
    if (!IsValid(ActorComponent))
        return;   
    ActorComponent->SetCanMoveAndState(false, ECharacterMovement::Walk);
    UCharacterMovementComponent *MovementComponent = Cast<UCharacterMovementComponent>(ActorComponent->GetMovementComponent());
    MovementComponent->SetMovementMode(EMovementMode::MOVE_Walking);
    bCanClimb = true;
}

float UCharacterMovementExtensionsLadde::GetDirection()
{
    return Direction;
}

void UCharacterMovementExtensionsLadde::StartClimbingLadder(AProject_HybriaCharacter *Character, ALadder *Ladder, float ZCorrection)
{
	if(!IsValid(Character)) return;

    Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);

	if(!IsValid(Ladder)) return;

	LadderBottom = Ladder->GetLadderBottom();
	LadderTop = Ladder->GetLadderTop();

	const FVector LadderForwardVector = Ladder->GetActorForwardVector();

	// Encontre a direção oposta
	const FVector InvertedForwardVector = LadderForwardVector * -1.0f;

	// Obtenha a rotação necessária para virar o personagem para a direção oposta
	const FRotator InvertedRotation = InvertedForwardVector.Rotation();
	const FRotator NewRotation = FRotator(0.0f, InvertedRotation.Yaw, 0.0f);

	// Defina a nova rotação do personagem
	Character->SetActorRotation(NewRotation);

    FLatentActionInfo Looll;
	Looll.CallbackTarget = this;
	FVector Location = FVector(Ladder->GetActorLocation().X, Ladder->GetActorLocation().Y, Character->GetActorLocation().Z + ZCorrection);

	Location += Character->GetActorForwardVector() * OffSet;
    

    UKismetSystemLibrary::MoveComponentTo(Character->GetCapsuleComponent(), Location, Character->GetActorRotation(), false, false, 0.1, false, EMoveComponentAction::Move, Looll);
}

void UCharacterMovementExtensionsLadde::SetLadderProperties(float InOffSet, float InBottomDistanceToDrop, float InTopDistanceToClimb, UAnimMontage* InEdgeJumpingClimbMontage)
{
    OffSet = InOffSet;
    BottomDistanceToDrop = InBottomDistanceToDrop;
    TopDistanceToClimb = InTopDistanceToClimb;
    EdgeJumpingClimbMontage = InEdgeJumpingClimbMontage;
}