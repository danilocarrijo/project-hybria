#include "CharacterMovementExtensions.h"
#include "Climb/CharacterMovementExtensionsClimb.h"
#include "EdgeJump/CharacterMovementExtensionsEdgeJump.h"
#include "../Project_HybriaCharacter.h"

UCharacterMovementExtensions::UCharacterMovementExtensions()
{

}

void UCharacterMovementExtensions::Tick(AProject_HybriaCharacter *Character)
{

    if (Character == nullptr)
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

void UCharacterMovementExtensions::ClimbEvent(UAnimMontage *ClimbMontage, float HangAnimRate, float ClimbAnimRate, int HangHandOffset, int HangZOffset)
{
    ClimbExtensions = NewObject<UCharacterMovementExtensionsClimb>();
    CurrMovement = ECharacterMovement::Walk;
    
    ClimbExtensions->HangAnimRate = HangAnimRate;
    ClimbExtensions->ClimbAnimRate = ClimbAnimRate;
    ClimbExtensions->HangHandOffset = HangHandOffset;
    ClimbExtensions->HangZOffset = HangZOffset;
}

void UCharacterMovementExtensions::EdgeJumpEvent()
{
    EdgeJumpExtensions = NewObject<UCharacterMovementExtensionsEdgeJump>();
}

void UCharacterMovementExtensions::FinishClimbing()
{
	ClimbExtensions->FinishClimbing();
}