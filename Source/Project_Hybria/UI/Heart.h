// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Heart.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_HYBRIA_API UHeart : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UHeart(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	void SetValue(float Value);

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMaterialInstanceDynamic* Material;
};
