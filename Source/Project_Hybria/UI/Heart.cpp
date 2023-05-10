// Fill out your copyright notice in the Description page of Project Settings.


#include "Heart.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Blueprint/UserWidget.h"
#include "Components/Overlay.h"
#include "Engine/Engine.h"

UHeart::UHeart(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{

    SizeBox = NewObject<USizeBox>(this, USizeBox::StaticClass(), TEXT("Size Box"));
    
    // Defina o tamanho desejado para o componente SizeBox
    SizeBox->SetWidthOverride(100.0f);
    SizeBox->SetHeightOverride(100.0f);

    if (SizeBox)
    {
        // Adiciona a imagem dentro do Size Box
        Heart = NewObject<UImage>(this, UImage::StaticClass(), TEXT("Heart image"));
        if (Heart)
        {
            // Adiciona a imagem dentro do Size Box
            SizeBox->SetContent(Heart);
        }
    }

    // Adicionar o SizeBox ao Overlay
    UOverlay* Overlay = Cast<UOverlay>(GetRootWidget());
    if (Overlay)
    {
        Overlay->AddChild(SizeBox);
    }
}

void UHeart::NativeConstruct()
{
    Super::NativeConstruct();
}

void UHeart::SetValue(float Value)
{
    if (IsValid(Material))
    {
        Material->SetScalarParameterValue("percent", Value);
    }
}