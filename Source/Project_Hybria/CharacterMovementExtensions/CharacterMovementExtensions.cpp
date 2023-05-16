#include "CharacterMovementExtensions.h"
#include "Climb/CharacterMovementExtensionsClimb.h"
#include "EdgeJump/CharacterMovementExtensionsEdgeJump.h"
#include "LadderClimbing/CharacterMovementExtensionsLadde.h"
#include "../Project_HybriaCharacter.h"
#include "Engine/Engine.h"
#include "../Ladder.h"
#include "Swimming/SwimmingMovementExtensions.h"
#include "Diving/DivingMovementExtensions.h"
#include "Templates/SharedPointer.h"

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

    SwimmingMovementExtensions = NewObject<USwimmingMovementExtensions>();

	DivingMovementExtensions = NewObject<UDivingMovementExtensions>();

	EdgeJumpExtensions = NewObject<UCharacterMovementExtensionsEdgeJump>();

	ClimbExtensions = NewObject<UCharacterMovementExtensionsClimb>();

	DivingMovementExtensions->DiveSpeed = DiveSpeed;

	DivingMovementExtensions->DiveBottomHitTolerance = DiveBottomHitTolerance;

	DivingMovementExtensions->DiveTopHitTolerance = DiveTopHitTolerance;
    
	DivingMovementExtensions->MaxBreath =  MaxBreath;
    
	DivingMovementExtensions->BreathCircleColor =  BreathCircleColor;
    
	DivingMovementExtensions->BreathCircleColorDanger =  BreathCircleColorDanger;
    
	DivingMovementExtensions->DangerZoneBreathPercentage =  DangerZoneBreathPercentage;
    
	DivingMovementExtensions->UnderwaterTimeCount =  UnderwaterTimeCount;
	
    SwimmingMovementExtensions->ZCorrection = WaterSurfaceZCorrection;

    SwimmingMovementExtensions->WaterRippleEffect  = WaterRippleEffect;

    SwimmingMovementExtensions->WaterSplashEffect  = WaterSplashEffect;

	LadderClimbingExtensions->LadderClimbSpeed = LadderClimbSpeed;
    
    LadderClimbingExtensions->SetLadderProperties(HandOffSet, BottomDistanceToDrop, TopDistanceToClimb, EdgeJumpingClimbMontage);
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


    bool bHitWaterSurface;
    bool bHitWall;

    switch (CurrMovement)
    {
        case ECharacterMovement::Walk:
            bHitWaterSurface = SwimmingMovementExtensions->CheckForWaterSurface(Character);
            if(!bHitWaterSurface)
            {
                ClimbExtensions->Tick(Character);
                EdgeJumpExtensions->Tick(Character);
                
            } else {
                CurrMovement = ECharacterMovement::Swimming;
                SwimmingMovementExtensions->StartSwimming(Character);
            }
            break;
        case ECharacterMovement::Swimming:
            bHitWall = ClimbExtensions->Tick(Character);
            if(bHitWall)
            {
                SwimmingMovementExtensions->StopSwimming();
            }
            break;
    case ECharacterMovement::Diving:
    	DivingMovementExtensions->Tick(DeltaTime, Character);
    	break;
        default:
            break;
    }
}

void UCharacterMovementExtensions::ClimbLadderUp()
{
    if(CurrMovement == ECharacterMovement::LadderClimbing)
	{
		MoveForward(1);
	}
}

void UCharacterMovementExtensions::ClimbLadderDown()
{
    if(CurrMovement == ECharacterMovement::LadderClimbing)
	{
		MoveForward(-1);
	}
}

void UCharacterMovementExtensions::OnStairCollision(AActor* OtherActor)
{
	ALadder* LadderActor = Cast<ALadder>(OtherActor);

	if(!IsValid(LadderClimbingExtensions)) return;

    CurrMovement = ECharacterMovement::LadderClimbing;
    bLockMovement = true;

    LadderClimbingExtensions->StartClimbingLadder(Cast<AProject_HybriaCharacter>(Character), LadderActor, ZCorrection);

}

void UCharacterMovementExtensions::FinishClimbing()
{
	if(!IsValid(ClimbExtensions)) return;

	ClimbExtensions->FinishClimbing();
}

void UCharacterMovementExtensions::FinishLadderClimbing()
{
	if(!IsValid(LadderClimbingExtensions)) return;

	LadderClimbingExtensions->FinishLadderClimbing(Cast<AProject_HybriaCharacter>(Character));
}

void UCharacterMovementExtensions::ChangeState(bool inbLockMoviment, ECharacterMovement Movement)
{
	bLockMovement = inbLockMoviment;
	CurrMovement = Movement;
}

void UCharacterMovementExtensions::StopClimbLadder()
{
	if(CurrMovement == ECharacterMovement::LadderClimbing)
	{
    	LadderClimbingExtensions->StopClimbingLadder();
	}
}

void UCharacterMovementExtensions::Jump()
{
    Cast<AProject_HybriaCharacter>(Character)->Jump();
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
        case ECharacterMovement::LadderClimbing:
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

void UCharacterMovementExtensions::MoveForwardWalk(const float Value) const
{
	if (!bLockMovement && (Cast<AProject_HybriaCharacter>(Character)->Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Cast<AProject_HybriaCharacter>(Character)->Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		Cast<AProject_HybriaCharacter>(Character)->AddMovementInput(Direction, Value);
	}
}

void UCharacterMovementExtensions::MoveForwardLadder(float Value)
{
	if(!IsValid(LadderClimbingExtensions)) return;
        
    LadderClimbingExtensions->Climb(Value, Cast<AProject_HybriaCharacter>(Character));
}

float UCharacterMovementExtensions::GetClimbingLadderDirection()
{
	if(!IsValid(LadderClimbingExtensions)) return 0.0;

    return LadderClimbingExtensions->GetDirection();
}

void UCharacterMovementExtensions::MoveRightWalk(float Value) const
{
	if (!bLockMovement && (Character->Controller != nullptr) && (Value != 0.0f))
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

void UCharacterMovementExtensions::EdgeClimbingFreeMovement()
{
	if(!IsValid(ClimbExtensions)) return;

	ClimbExtensions->FreeMovement();
}

void UCharacterMovementExtensions::StartDiving()
{
	if(!IsValid(DivingMovementExtensions)) return;

	if(!IsValid(SwimmingMovementExtensions)) return;

	CurrMovement = ECharacterMovement::Diving;

	SwimmingMovementExtensions->StopSwimming();

	DivingMovementExtensions->StartDiving(Cast<AProject_HybriaCharacter>(Character));
}

void UCharacterMovementExtensions::StopDiving()
{
	if(!IsValid(DivingMovementExtensions)) return;

	DivingMovementExtensions->StopDiving(Cast<AProject_HybriaCharacter>(Character));
}

int UCharacterMovementExtensions::GetDivingDirection() const
{
	if(!IsValid(DivingMovementExtensions)) return 0;

	return DivingMovementExtensions->GetDivingDirection();
}

float UCharacterMovementExtensions::GetCurrBreath() const
{
	if(!IsValid(DivingMovementExtensions)) return 0;

	return DivingMovementExtensions->GetCurrBreath();
}

void UCharacterMovementExtensions::GoToSurface()
{
	if(!IsValid(SwimmingMovementExtensions)) return;

	CurrMovement = ECharacterMovement::Swimming;

	return SwimmingMovementExtensions->GoToSurface(Character);
}

