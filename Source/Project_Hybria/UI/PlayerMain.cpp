// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMain.h"
#include "Engine/GameViewportClient.h"
#include "GameFramework/PlayerController.h"
#include "Components/WrapBox.h"
#include "Heart.h"
#include "Algo/Reverse.h"

void UPlayerMain::NativeConstruct()
{

}

void UPlayerMain::AddHearts(int qtd, bool bClear)
{
    if (bClear)
    {
        // Limpa todos os filhos do Wrap Box
        WrapBox->ClearChildren();
    }

    
    // Cria um loop para adicionar corações ao Wrap Box com base na vida atual do jogador
    for (int32 i = 0; i < qtd; i++)
    {
        // Cria uma instância do widget UHeart
        UUserWidget* Heart = CreateWidget<UUserWidget>(GetWorld(), HeartWidget);
        

        // Define o widget UHeart como filho do Wrap Box
        if (Heart && WrapBox)
        {
            Heart->AddToViewport();
            WrapBox->AddChildToWrapBox(Heart);
        }
    }
}

void UPlayerMain::UpdateHearts(float Health)
{
    TArray<UWidget*> Hearts = WrapBox->GetAllChildren();

    //Algo::Reverse(Hearts);

    float RemainingHearts = 0;
    float FloorHeath = FMath::Floor(Health);
    float RemainingHealth = Health - FloorHeath;

    for (size_t i = 0; i < FloorHeath; i++)
    {
        UHeart *Heart = Cast<UHeart>(Hearts[i]);

        if(IsValid(Heart))
        {
            Heart->SetValue(1);
        }

        RemainingHearts += 1;
    }

    if (RemainingHealth != 0)
    {
        UHeart *Heart = Cast<UHeart>(Hearts[RemainingHearts]);

        if(IsValid(Heart))
        {
            Heart->SetValue(RemainingHealth);
        }

        RemainingHearts += 1;
    }

    if (RemainingHearts >= Hearts.Num()) return;

    for (size_t i = RemainingHearts; i < Hearts.Num(); i++)
    {
        UHeart *Heart = Cast<UHeart>(Hearts[i]);

        if(IsValid(Heart))
        {
            Heart->SetValue(0);
        }
    }
}