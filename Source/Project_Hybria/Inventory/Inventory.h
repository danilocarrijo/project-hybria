#pragma once

#include "CoreMinimal.h"
#include "InventoryType.h"
#include "Blueprint/UserWidget.h"
#include "Inventory.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PROJECT_HYBRIA_API UInventory : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInventory* InventoryUp;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInventory* InventoryDown;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInventory* InventoryLeft;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInventory* InventoryRight;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UInventorySlot*> Slots;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EInventoryType InventoryType;

	UFUNCTION(BlueprintNativeEvent)
	void OnUpKeyEvent();

	UFUNCTION(BlueprintNativeEvent)
	void OnDownKeyEvent();

	UFUNCTION(BlueprintNativeEvent)
	void OnRightKeyEvent();

	UFUNCTION(BlueprintNativeEvent)
	void OnLeftKeyEvent();

	UFUNCTION(BlueprintCallable)
	void SetSlots();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UItem*> Items;
};
