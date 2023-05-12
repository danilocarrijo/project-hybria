#pragma once

#include "CoreMinimal.h"
#include "HealthSystem.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_HYBRIA_API UHealthSystem: public UActorComponent
{
    GENERATED_BODY()
public:
    UHealthSystem();

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float MaxHealth;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float CurrHealth;

    void InitUI(class UPlayerMain* PlayerMainInstance);

    void TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser);
    
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	class UPlayerMain* PlayerMainInstance;
};