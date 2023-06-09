// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterMovement.h"
#include "CharacterMovementExtensions/CharacterMovementExtensions.h"
#include "Project_HybriaCharacter.generated.h"

UCLASS(config=Game)
class AProject_HybriaCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AProject_HybriaCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void MoveForward(float AxisValue);
	
	void MoveRight(float AxisValue);
	// End of APawn interface
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	void PlayMontage(class UAnimMontage* Montage, float Rate);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCharacterMovementExtensions* CharacterMovementExtensionsHandler;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UHealthSystem* HealthSystem;

	void SetCanMoveAndState(bool bCanMove, ECharacterMovement Movement);

    UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> PlayerWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsGamePaused = false;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void GoToSurface() const;

	void SetGamePaused();

	void MenuUp();

	void MenuDown();

	void MenuRight();

	void MenuLeft();
	
private:

	UPROPERTY(EditAnywhere)
		float TraceDistance = 50;

	bool bIsGrounded = false;

	UPROPERTY(EditAnywhere)
	class UPlayerMain* PlayerMainInstance;

};

