// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_HYBRIA_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Position;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsSelected = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString ItemName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bHasObject = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* IconTexture;

	UFUNCTION()
	void Set(TArray<class UItem*> Items);
};
