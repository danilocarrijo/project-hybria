// Fill out your copyright notice in the Description page of Project Settings.


#include "Heart.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Blueprint/UserWidget.h"
#include "Components/Overlay.h"

void UHeart::NativeConstruct()
{
    Super::NativeConstruct();

    SizeBox = NewObject<USizeBox>(this, USizeBox::StaticClass(), TEXT("Size Box"));

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