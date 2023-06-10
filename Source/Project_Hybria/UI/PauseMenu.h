#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_HYBRIA_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInventory* FocusedInventory;

	UFUNCTION(BlueprintCallable)
	void OnUpKeyEvent();

	UFUNCTION(BlueprintCallable)
	void OnDownKeyEvent();

	UFUNCTION(BlueprintCallable)
	void OnRightKeyEvent();

	UFUNCTION(BlueprintCallable)
	void OnLeftKeyEvent();

private:
};
