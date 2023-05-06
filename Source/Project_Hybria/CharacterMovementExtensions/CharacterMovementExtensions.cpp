#include "CharacterMovementExtensions.h"
#include "Climb/CharacterMovementExtensionsClimb.h"
#include "EdgeJump/CharacterMovementExtensionsEdgeJump.h"
#include "LadderClimbing/CharacterMovementExtensionsLadde.h"
#include "../Project_HybriaCharacter.h"
#include "Engine/Engine.h"
#include "GameFramework/CharacterMovementComponent.h"

UCharacterMovementExtensions::UCharacterMovementExtensions()
{

}

void UCharacterMovementExtensions::Tick(AProject_HybriaCharacter *Character)
{
    if (!IsValid(Character))
        return;

    switch (CurrMovement)
    {
        case ECharacterMovement::Walk:
            ClimbExtensions->Tick(Character);
            EdgeJumpExtensions->Tick(Character);
            break;
        default:
            break;
    }
}

void UCharacterMovementExtensions::Init(AProject_HybriaCharacter *Character)
{
    LadderClimbingExtensions = NewObject<UCharacterMovementExtensionsLadde>();

    LadderClimbingExtensions->LadderClimbSpeed = Character->LadderClimbSpeed;

    EdgeJumpExtensions = NewObject<UCharacterMovementExtensionsEdgeJump>();

    ClimbExtensions = NewObject<UCharacterMovementExtensionsClimb>();
    CurrMovement = ECharacterMovement::Walk;
    
    ClimbExtensions->HangAnimRate = Character->HangAnimRate;
    ClimbExtensions->ClimbAnimRate = Character->ClimbAnimRate;
    ClimbExtensions->HangHandOffset = Character->HangHandOffset;
    ClimbExtensions->HangZOffset = Character->HangZOffset;
}

void UCharacterMovementExtensions::FinishClimbing()
{
	ClimbExtensions->FinishClimbing();
}

void UCharacterMovementExtensions::ChangeState(bool inbLockMoviment, ECharacterMovement Movement, AProject_HybriaCharacter *Character)
{
	bLockMoviment = inbLockMoviment;
	CurrMovement = Movement;
}

void UCharacterMovementExtensions::Jump(AProject_HybriaCharacter *Character)
{
    Character->Jump();
}

void UCharacterMovementExtensions::MoveForward(float Value, AProject_HybriaCharacter *Character)
{
    switch (CurrMovement)
    {
        case ECharacterMovement::Walk:
            MoveForwardWalk(Value, Character);
            break;
        case ECharacterMovement::LadderClibing:
            MoveForwardLadder(Value, Character);
            break;
        default:
            break;
    }
}

void UCharacterMovementExtensions::MoveRight(float Value, AProject_HybriaCharacter *Character)
{
    switch (CurrMovement)
    {
        case ECharacterMovement::Walk:
            MoveRightWalk(Value, Character);
            break;
        default:
            break;
    }
}

void UCharacterMovementExtensions::MoveForwardWalk(float Value, AProject_HybriaCharacter *Character)
{
	if (!bLockMoviment && (Character->Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Character->Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		Character->AddMovementInput(Direction, Value);
	}
}

void UCharacterMovementExtensions::MoveForwardLadder(float Value, AProject_HybriaCharacter *Character)
{
	if(!IsValid(LadderClimbingExtensions)) return;
        
    auto bDrop = LadderClimbingExtensions->DropBottom(Character);

    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("A distância entre os pontos é %d"), bDrop));

    if (bDrop)
    {
        CurrMovement = ECharacterMovement::Walk;
        bLockMoviment = false;
        Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
        StopClimbingLadder();
    }

	if (!bDrop && Value != 0.0f)
	{
        LadderClimbingExtensions->Climb(Value, Character);
	}
}

void UCharacterMovementExtensions::StopClimbingLadder()
{
	if(!IsValid(LadderClimbingExtensions)) return;

    LadderClimbingExtensions->StopClimbingLadder();
}

void UCharacterMovementExtensions::StartClimbingLadder(AProject_HybriaCharacter *Character, ALadder *Ladder, float ZCorrection, float OffSet, float BottomDistanceToDrop)
{
	if(!IsValid(LadderClimbingExtensions)) return;
    
    LadderClimbingExtensions->SetLadderProperties(OffSet, BottomDistanceToDrop);

    CurrMovement = ECharacterMovement::LadderClibing;
    bLockMoviment = true;

    LadderClimbingExtensions->StartClimbingLadder(Character, Ladder, ZCorrection);

}

float UCharacterMovementExtensions::GetClimbingLadderDirection()
{
	if(!IsValid(LadderClimbingExtensions)) return 0.0;

    return LadderClimbingExtensions->GetDirection();
}

void UCharacterMovementExtensions::MoveRightWalk(float Value, AProject_HybriaCharacter *Character)
{
	if (!bLockMoviment && (Character->Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Character->Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		Character->AddMovementInput(Direction, Value);
	}
}

