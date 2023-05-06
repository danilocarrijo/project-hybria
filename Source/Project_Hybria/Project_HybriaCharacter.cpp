// Copyright Epic Games, Inc. All Rights Reserved.

#include "Project_HybriaCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Character.h"
#include "CharacterMovementExtensions/CharacterMovementExtensions.h"
#include "Ladder.h"

//////////////////////////////////////////////////////////////////////////
// AProject_HybriaCharacter

// Called when the game starts or when spawned
void AProject_HybriaCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(CharacterMovementExtensionsHandler)) {
		

	CharacterMovementExtensionsHandler = NewObject<UCharacterMovementExtensions>();

	CharacterMovementExtensionsHandler->CurrMovement = ECharacterMovement::Walk;
	CharacterMovementExtensionsHandler->Init(this);
	}
}

AProject_HybriaCharacter::AProject_HybriaCharacter()
{
	ClimbMontage = CreateDefaultSubobject<UAnimMontage>(TEXT("Climb Montage"));

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rate for input
	TurnRateGamepad = 50.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;			 // Character moves in the direction of input...
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;		// The camera follows at this distance behind the character
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false;								// Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character)
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

// Called every frame
void AProject_HybriaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(CharacterMovementExtensionsHandler == nullptr) return;

	//UE_LOG(LogTemp, Display, TEXT("%s"),CharacterMovementExtensionsHandler->bLockMoviment);
	CharacterMovementExtensionsHandler->Tick(this);
}

void AProject_HybriaCharacter::PlayMontage(class UAnimMontage* Montage, float Rate)
{
    //UE_LOG(LogTemp, Display, TEXT("%s"), *Montage->GetName());
	PlayAnimMontage(Montage, 1.0f);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AProject_HybriaCharacter::SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("ClimbLadderUp", IE_Pressed, this, &AProject_HybriaCharacter::ClimbLadderUp);
    PlayerInputComponent->BindAction("ClimbLadderUp", IE_Released, this, &AProject_HybriaCharacter::StopClimbLadder);

	PlayerInputComponent->BindAction("ClimbLadderDown", IE_Pressed, this, &AProject_HybriaCharacter::ClimbLadderDown);
    PlayerInputComponent->BindAction("ClimbLadderDown", IE_Released, this, &AProject_HybriaCharacter::StopClimbLadder);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AProject_HybriaCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AProject_HybriaCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	/*PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &AProject_HybriaCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &AProject_HybriaCharacter::LookUpAtRate);*/

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AProject_HybriaCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AProject_HybriaCharacter::TouchStopped);
}

void AProject_HybriaCharacter::ClimbLadderUp()
{
	if (!IsValid(CharacterMovementExtensionsHandler)) return;

	if(CharacterMovementExtensionsHandler->CurrMovement == ECharacterMovement::LadderClibing)
	{
		CharacterMovementExtensionsHandler->MoveForward(1, this);
	}
}

void AProject_HybriaCharacter::ClimbLadderDown()
{
	if (!IsValid(CharacterMovementExtensionsHandler)) return;

	if(CharacterMovementExtensionsHandler->CurrMovement == ECharacterMovement::LadderClibing)
	{
		CharacterMovementExtensionsHandler->MoveForward(-1, this);
	}
}

void AProject_HybriaCharacter::StopClimbLadder()
{
	if (!IsValid(CharacterMovementExtensionsHandler)) return;

	if(CharacterMovementExtensionsHandler->CurrMovement == ECharacterMovement::LadderClibing)
	{
    	CharacterMovementExtensionsHandler->StopClimbingLadder();
	}
}

void AProject_HybriaCharacter::OnStairEndCollision(AActor* OtherActor)
{
	//SetCanMoveAndState(false, ECharacterMovement::Walk);
	Jump(); 
}

void AProject_HybriaCharacter::OnStairCollision(AActor* OtherActor)
{
	if (!IsValid(CharacterMovementExtensionsHandler)) return;

	ALadder* Ladder = Cast<ALadder>(OtherActor);

	if(!IsValid(Ladder)) return;

    CharacterMovementExtensionsHandler->StartClimbingLadder(this, Ladder, ZCorrection, HandOffSet, BottomDistanceToDrop);

}

float AProject_HybriaCharacter::GetClimbingLadderDirection()
{
	if (!IsValid(CharacterMovementExtensionsHandler)) return 0.0;

    return CharacterMovementExtensionsHandler->GetClimbingLadderDirection();
}

void AProject_HybriaCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (!IsValid(CharacterMovementExtensionsHandler)) return;

	if (!CharacterMovementExtensionsHandler->bLockMoviment)
		Jump();
}

void AProject_HybriaCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void AProject_HybriaCharacter::TurnAtRate(float Rate)
{
	if (!IsValid(CharacterMovementExtensionsHandler)) return;
	// calculate delta for this frame from the rate information

	if (!CharacterMovementExtensionsHandler->bLockMoviment)
		AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AProject_HybriaCharacter::LookUpAtRate(float Rate)
{
	if (!IsValid(CharacterMovementExtensionsHandler)) return;
	// calculate delta for this frame from the rate information

	if (!CharacterMovementExtensionsHandler->bLockMoviment)
		AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AProject_HybriaCharacter::MoveForward(float Value)
{
	if (!IsValid(CharacterMovementExtensionsHandler)) return;
	CharacterMovementExtensionsHandler->MoveForward(Value, this);
}

void AProject_HybriaCharacter::MoveRight(float Value)
{
	if (!IsValid(CharacterMovementExtensionsHandler)) return;
	CharacterMovementExtensionsHandler->MoveRight(Value, this);
}

void AProject_HybriaCharacter::FinishClimbing()
{
    if ( CharacterMovementExtensionsHandler->CurrMovement == ECharacterMovement::Clibing )
	CharacterMovementExtensionsHandler->FinishClimbing();
}

void AProject_HybriaCharacter::SetCanMoveAndState(bool bLockMoviment, ECharacterMovement Movement) 
{
	if (!IsValid(CharacterMovementExtensionsHandler)) return;

	CharacterMovementExtensionsHandler->ChangeState(bLockMoviment, Movement, this);
}

ECharacterMovement AProject_HybriaCharacter::GetCurrMovement()
{
	if (!IsValid(CharacterMovementExtensionsHandler)) return ECharacterMovement::Walk;
	return CharacterMovementExtensionsHandler->CurrMovement;
}