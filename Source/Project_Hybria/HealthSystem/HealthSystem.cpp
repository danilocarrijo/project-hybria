#include "HealthSystem.h"
#include "../UI/PlayerMain.h"

UHealthSystem::UHealthSystem()
{
}


// Called when the game starts
void UHealthSystem::BeginPlay()
{
	Super::BeginPlay();

    CurrHealth = MaxHealth;
}

void UHealthSystem::InitUI(UPlayerMain* InPlayerMainInstance)
{
    PlayerMainInstance = InPlayerMainInstance;

    if (IsValid(PlayerMainInstance))
    {
        PlayerMainInstance->AddHearts(MaxHealth, true);
    }
}

void UHealthSystem::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
    CurrHealth -= DamageAmount;

    if (IsValid(PlayerMainInstance) && CurrHealth > 0 )
    {
        PlayerMainInstance->UpdateHearts(CurrHealth);
    } else if (IsValid(PlayerMainInstance) && CurrHealth <= 0 )
    {
        PlayerMainInstance->UpdateHearts(0);
    }
}