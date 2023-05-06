#include "CharacterMovementExtensionsLadde.h"
#include "../../Project_HybriaCharacter.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/Engine.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../../Ladder.h"

bool UCharacterMovementExtensionsLadde::DropBottom(AProject_HybriaCharacter *Character)
{
    float Distance = GetBottomDistance(Character);

    return Distance < BottomDistanceToDrop;
}

float UCharacterMovementExtensionsLadde::GetBottomDistance(AProject_HybriaCharacter *Character)
{
    FVector ActorLocation = Character->GetCapsuleComponent()->GetComponentLocation();

    float Distance = ActorLocation.Z - LadderBottom.Z;
    Distance = FMath::Abs(Distance);

    return Distance;
}

void UCharacterMovementExtensionsLadde::Climb(float Value, AProject_HybriaCharacter *Character)
{
    if(Value > 0)
        Direction = 1;
    else
        Direction = -1;

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

float UCharacterMovementExtensionsLadde::GetDirection()
{
    return Direction;
}

void UCharacterMovementExtensionsLadde::StartClimbingLadder(AProject_HybriaCharacter *Character, ALadder *Ladder, float ZCorrection)
{
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
	FVector Location = FVector(Character->GetActorLocation().X, Character->GetActorLocation().Y, Character->GetActorLocation().Z + ZCorrection);

	Location += Character->GetActorForwardVector() * OffSet;

    UKismetSystemLibrary::MoveComponentTo(Character->GetCapsuleComponent(), Location, Character->GetActorRotation(), false, false, 0.1, false, EMoveComponentAction::Move, Looll);
}

void UCharacterMovementExtensionsLadde::SetLadderProperties(float InOffSet, float InBottomDistanceToDrop)
{
    OffSet = InOffSet;
    BottomDistanceToDrop = InBottomDistanceToDrop;
}