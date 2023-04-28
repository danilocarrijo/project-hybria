#include "CharacterMovementExtensions.h"
#include "Climb/CharacterMovementExtensionsClimb.h"
#include "../Project_HybriaCharacter.h"

UCharacterMovementExtensions::UCharacterMovementExtensions()
{

    ClimbExtensions = NewObject<UCharacterMovementExtensionsClimb>();
    CurrMovement = ECharacterMovement::Walk;
}

void UCharacterMovementExtensions::Tick(AProject_HybriaCharacter *Character,
                                        UWorld *Word)
{

    if (Character == nullptr || Word == nullptr)
        return;

    switch (CurrMovement)
    {
        case ECharacterMovement::Walk:
            ClimbExtensions->Tick(Character,
                                Word);
            break;
        default:
            break;
    }
}

void UCharacterMovementExtensions::ClimbEvent(UAnimMontage *ClimbMontage)
{
    ClimbExtensions->MyMontage = ClimbMontage;
}

void UCharacterMovementExtensions::FinishClimbing()
{
	ClimbExtensions->FinishClimbing();
}