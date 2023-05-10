#include "CharacterMovementExtensions.h"
#include "Climb/CharacterMovementExtensionsClimb.h"
#include "EdgeJump/CharacterMovementExtensionsEdgeJump.h"
#include "LadderClimbing/CharacterMovementExtensionsLadde.h"
#include "../Project_HybriaCharacter.h"
#include "Engine/Engine.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Ladder.h"
#include "Swimming/SimmingMovementExtensions.h"

UCharacterMovementExtensions::UCharacterMovementExtensions()
{
	PrimaryComponentTick.bCanEverTick = true;
    
	ClimbMontage = CreateDefaultSubobject<UAnimMontage>(TEXT("Climb Montage"));
	EdgeJumpingClimbMontage = CreateDefaultSubobject<UAnimMontage>(TEXT("Edge Jumping Climb Montage"));
}

// Called when the game starts
void UCharacterMovementExtensions::BeginPlay()
{
	Super::BeginPlay();

    Character = Cast<AProject_HybriaCharacter>(GetOwner());

    LadderClimbingExtensions = NewObject<UCharacterMovementExtensionsLadde>();

    SimmingMovementExtensions = NewObject<USimmingMovementExtensions>();

    SimmingMovementExtensions->ZCorrection = WaterSurfaceZCorrection;

    LadderClimbingExtensions->LadderClimbSpeed = LadderClimbSpeed;    
    
    LadderClimbingExtensions->SetLadderProperties(HandOffSet, BottomDistanceToDrop, TopDistanceToClimb, EdgeJumpingClimbMontage);

    EdgeJumpExtensions = NewObject<UCharacterMovementExtensionsEdgeJump>();

    ClimbExtensions = NewObject<UCharacterMovementExtensionsClimb>();
    CurrMovement = ECharacterMovement::Walk;
    
    ClimbExtensions->HangAnimRate = HangAnimRate;
    ClimbExtensions->ClimbAnimRate = ClimbAnimRate;
    ClimbExtensions->HangHandOffset = HangHandOffset;
    ClimbExtensions->HangZOffset = HangZOffset;
    ClimbExtensions->ClimbMontage = ClimbMontage;
	
}

void UCharacterMovementExtensions::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!IsValid(Character))
        return;

    bool bHitWaterSurface = false;

    switch (CurrMovement)
    {
        case ECharacterMovement::Walk:
            bHitWaterSurface = SimmingMovementExtensions->CheckForWaterSurface(Character);
            if(!bHitWaterSurface)
            {
                ClimbExtensions->Tick(Character);
                EdgeJumpExtensions->Tick(Character);
                
            } else {
                CurrMovement = ECharacterMovement::Swimming;
                SimmingMovementExtensions->StartSwimming(Character);
            }
            break;
        case ECharacterMovement::Swimming:
            ClimbExtensions->Tick(Character);
            break;
        default:
            break;
    }
}

void UCharacterMovementExtensions::ClimbLadderUp()
{
    if(CurrMovement == ECharacterMovement::LadderClibing)
	{
		MoveForward(1);
	}
}

void UCharacterMovementExtensions::ClimbLadderDown()
{
    if(CurrMovement == ECharacterMovement::LadderClibing)
	{
		MoveForward(-1);
	}
}

void UCharacterMovementExtensions::OnStairCollision(AActor* OtherActor)
{
	ALadder* LadderActor = Cast<ALadder>(OtherActor);

	if(!IsValid(LadderClimbingExtensions)) return;

    CurrMovement = ECharacterMovement::LadderClibing;
    bLockMoviment = true;

    LadderClimbingExtensions->StartClimbingLadder(Character, LadderActor, ZCorrection);

}

void UCharacterMovementExtensions::FinishClimbing()
{
	if(!IsValid(ClimbExtensions)) return;

	ClimbExtensions->FinishClimbing();
}

void UCharacterMovementExtensions::FinishLadderClimbing()
{
	if(!IsValid(LadderClimbingExtensions)) return;

	LadderClimbingExtensions->FinishLadderClimbing(Character);
}

void UCharacterMovementExtensions::ChangeState(bool inbLockMoviment, ECharacterMovement Movement)
{
	bLockMoviment = inbLockMoviment;
	CurrMovement = Movement;
}

void UCharacterMovementExtensions::StopClimbLadder()
{
	if(CurrMovement == ECharacterMovement::LadderClibing)
	{
    	LadderClimbingExtensions->StopClimbingLadder();
	}
}

void UCharacterMovementExtensions::Jump()
{
    Character->Jump();
}

void UCharacterMovementExtensions::MoveForward(float Value)
{
    switch (CurrMovement)
    {
        case ECharacterMovement::Walk:
            MoveForwardWalk(Value);
            break;
        case ECharacterMovement::Swimming:
            MoveForwardWalk(Value);
            break;
        case ECharacterMovement::LadderClibing:
            MoveForwardLadder(Value);
            break;
        default:
            break;
    }
}

void UCharacterMovementExtensions::MoveRight(float Value)
{
    switch (CurrMovement)
    {
        case ECharacterMovement::Walk:
            MoveRightWalk(Value);
            break;
        case ECharacterMovement::Swimming:
            MoveRightWalk(Value);
            break;
        default:
            break;
    }
}

void UCharacterMovementExtensions::MoveForwardWalk(float Value)
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

void UCharacterMovementExtensions::MoveForwardLadder(float Value)
{
	if(!IsValid(LadderClimbingExtensions)) return;
        
    LadderClimbingExtensions->Climb(Value, Character);
}

float UCharacterMovementExtensions::GetClimbingLadderDirection()
{
	if(!IsValid(LadderClimbingExtensions)) return 0.0;

    return LadderClimbingExtensions->GetDirection();
}

void UCharacterMovementExtensions::MoveRightWalk(float Value)
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

