#include "DivingMovementExtensions.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Project_Hybria/Project_HybriaCharacter.h"
#include "Project_Hybria/HybriaLibrary/HybriaLibrary.h"

bool UDivingMovementExtensions::CheckForBottom(AProject_HybriaCharacter* Character) const
{
	const FVector End = Character->GetActorLocation() + FVector(0, 0, -1000000);

	if (FHitResult FloorHit; UHybriaLibrary::SphereTraceByChannel(Character,
	                                                              Character->GetWorld(),
	                                                              Character->GetActorLocation(),
	                                                              End,
	                                                              10.f,
	                                                              ECC_WorldStatic,
	                                                              FloorHit,
	                                                              true))
	{
		if(const float Distance = FloorHit.Location.Z - Character->GetActorLocation().Z; FMath::Abs(Distance) < DiveBottomHitTolerance)
		{
			return true;
		}
		return false;
	}

	return false;
}

bool UDivingMovementExtensions::CheckForTop(AProject_HybriaCharacter* Character) const
{
	const FVector Start = Character->GetActorLocation() + FVector(0, 0, 300);
	
	if (FHitResult WaterHit; UHybriaLibrary::SphereTraceByChannel(Character,
																  Character->GetWorld(),
																  Start,
																  Character->GetActorLocation(),
																  10.f,
																  ECC_GameTraceChannel2,
																  WaterHit,
																  true))
	{
		if(const float Distance = WaterHit.Location.Z - Character->GetActorLocation().Z; FMath::Abs(Distance) < DiveTopHitTolerance)
		{
			return true;
		}
		return false;
	}

	return false;
}

UDivingMovementExtensions::UDivingMovementExtensions()
{
}

void UDivingMovementExtensions::Tick(float DeltaTime, AProject_HybriaCharacter *Character)
{
	if (DivingDirection == -1 && CheckForBottom(Character))
	{
		StopDiving(Character);
	}
	if (DivingDirection == 1 && CheckForTop(Character))
	{
		Character->GoToSurface();
	}

	TickTime += DeltaTime;


	if (TickTime >= UnderwaterTimeCount)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), CurrBreath));
		TickTime = 0.0f;
		CurrBreath -= 0.1;
		if(CurrBreath < 0)
		{
			Character->TakeDamage(0.25, FDamageEvent(), Character->GetInstigatorController(), Character);
		}
	}

	const FVector UpVector = FVector(0.0f, 0.0f, 1.0f * DivingDirection);

	const FVector NewLocation = Character->GetActorLocation() + UpVector;

	Character->GetCharacterMovement()->MoveUpdatedComponent(UpVector, Character->GetActorRotation(), true);
    
	Character->SetActorLocation(NewLocation);
}

void UDivingMovementExtensions::StartDiving(AProject_HybriaCharacter *Character)
{
	DivingDirection = -1;

	CurrBreath = MaxBreath;
}

void UDivingMovementExtensions::StopDiving(AProject_HybriaCharacter *Character)
{
	DivingDirection = 1;
}

int UDivingMovementExtensions::GetDivingDirection() const
{
	return DivingDirection;
}

float UDivingMovementExtensions::GetCurrBreath() const
{
	return CurrBreath;
}
