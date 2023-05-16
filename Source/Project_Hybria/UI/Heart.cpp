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