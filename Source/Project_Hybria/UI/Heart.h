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
	virtual void NativeConstruct() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
    class UImage* Heart;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
    class USizeBox* SizeBox;

private:
	class UMaterialInstanceDynamic* Material;
};
