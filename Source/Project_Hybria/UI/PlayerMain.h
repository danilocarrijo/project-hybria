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
    void AddHearts(int qtd, bool bClear);

    UFUNCTION(BlueprintCallable)
    void UpdateHearts(float Health);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
    class UWrapBox* WrapBox;

    UPROPERTY(EditAnywhere)
    TSubclassOf<class UUserWidget> HeartWidget;
};
