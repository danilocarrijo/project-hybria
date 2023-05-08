#pragma once

#include "CoreMinimal.h"
#include "../CharacterMovement.h"
#include "Climb/CharacterMovementExtensionsClimb.h"
#include "CharacterMovementExtensions.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_HYBRIA_API UCharacterMovementExtensions: public UActorComponent
{
    GENERATED_BODY()
private:
    class UCharacterMovementExtensionsClimb* ClimbExtensions;
    class UCharacterMovementExtensionsEdgeJump* EdgeJumpExtensions;
    class UCharacterMovementExtensionsLadde* LadderClimbingExtensions;

	void MoveForwardWalk(float Value);

	void MoveRightWalk(float Value);

    void MoveForwardLadder(float Value);

public:
    UCharacterMovementExtensions();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Climb Movement")
        class UAnimMontage* ClimbMontage;


    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Climb Movement")
        float HangAnimRate = 0.5f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Climb Movement")
        float ClimbAnimRate = 0.5f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Climb Movement")
        int HangHandOffset = 2;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Climb Movement")
        int HangZOffset = 200;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Ladder Climb Movement")
        int LadderClimbSpeed = 200;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Ladder Climb Movement")
        int HandOffSet = 20;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Ladder Climb Movement")
        float ZCorrection = 20;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Ladder Climb Movement")
        float BottomDistanceToDrop = 20;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Ladder Climb Movement")
        float TopDistanceToClimb = 20;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Ladder Climb Movement")
        class UAnimMontage* EdgeJumpingClimbMontage;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

    class AProject_HybriaCharacter *Character;

public:

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECharacterMovement CurrMovement = ECharacterMovement::Walk;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MyActor")
        bool bLockMoviment = false;

    void ChangeState(bool bLockMoviment, ECharacterMovement Movement);

    UFUNCTION(BlueprintCallable)
    void Jump();

    UFUNCTION(BlueprintCallable)
	void MoveForward(float Value);

    UFUNCTION(BlueprintCallable)
	void MoveRight(float Value);

    UFUNCTION(BlueprintCallable)
	void ClimbLadderUp();

    UFUNCTION(BlueprintCallable)
	void ClimbLadderDown();

    UFUNCTION(BlueprintCallable)
    void OnStairCollision(class AActor* OtherActor);

    UFUNCTION(BlueprintCallable)
    void FinishClimbing();

    UFUNCTION(BlueprintCallable)
    void FinishLadderClimbing();

    UFUNCTION(BlueprintCallable)
    void StopClimbLadder();

    UFUNCTION(BlueprintCallable)
	float GetClimbingLadderDirection();
};