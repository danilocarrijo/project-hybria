#pragma once

#include "CoreMinimal.h"
#include "../CharacterMovement.h"
#include "CharacterMovementExtensions.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_HYBRIA_API UCharacterMovementExtensions: public UActorComponent
{
    GENERATED_BODY()
private:
    UPROPERTY()
    class UCharacterMovementExtensionsClimb* ClimbExtensions;    
    
    UPROPERTY()
    class UCharacterMovementExtensionsEdgeJump* EdgeJumpExtensions;
    
    UPROPERTY()
    class UCharacterMovementExtensionsLadde* LadderClimbingExtensions;
    
    UPROPERTY()
    class USwimmingMovementExtensions* SwimmingMovementExtensions;
    
    UPROPERTY()
    class UDivingMovementExtensions* DivingMovementExtensions;

    UPROPERTY()
    class AProject_HybriaCharacter* Character;

	void MoveForwardWalk(float Value) const;

	void MoveRightWalk(float Value) const;

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

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Swim Movement")
        float WaterSurfaceZCorrection;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Swim Movement")
        class UNiagaraSystem* WaterRippleEffect;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Swim Movement")
        class UNiagaraSystem* WaterSplashEffect;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Swim Movement")
    float DiveSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Swim Movement")
    float DiveBottomHitTolerance;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Swim Movement")
    float DiveTopHitTolerance;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Swim Movement")
    float CurrBreath;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Swim Movement")
    float MaxBreath;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Swim Movement")
    float UnderwaterTimeCount;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Swim Movement")
    float DangerZoneBreathPercentage;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Swim Movement")
    FLinearColor BreathCircleColor;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Swim Movement")
    FLinearColor BreathCircleColorDanger;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECharacterMovement CurrMovement = ECharacterMovement::Walk;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MyActor")
        bool bLockMovement = false;

    void ChangeState(bool bLockMovement, ECharacterMovement Movement);

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

    UFUNCTION(BlueprintCallable)
    void EdgeClimbingFreeMovement();

    UFUNCTION(BlueprintCallable)
    void StartDiving();

    UFUNCTION(BlueprintCallable)
    void StopDiving();

    UFUNCTION(BlueprintCallable)
    int GetDivingDirection() const;

    UFUNCTION(BlueprintCallable)
    float GetCurrBreath() const;
    
    void GoToSurface();
};