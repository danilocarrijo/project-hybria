// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ladder.generated.h"

UCLASS()
class PROJECT_HYBRIA_API ALadder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALadder();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Helper)
	class UArrowComponent* TopArrow;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Helper)
	class UArrowComponent* BottomArrow;

	UPROPERTY(EditAnywhere, Category = Physics)
	class UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Defaults)
	class UStaticMesh* LadderMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Defaults)
	float PieceSize = 32;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Defaults)
	float Offset = 200;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Defaults, Meta = (MakeEditWidget = true))
	FVector EndOfLadder;

    UFUNCTION(BlueprintCallable)
    void MakeLadder();

	virtual void OnConstruction(const FTransform& Transform) override;

	FVector GetLadderBottom();

	FVector GetLadderTop();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
