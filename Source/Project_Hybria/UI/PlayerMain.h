// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerMain.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_HYBRIA_API UPlayerMain : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

    UFUNCTION(BlueprintCallable)
    void AddHeart();
};
