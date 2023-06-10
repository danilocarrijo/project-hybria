#include "PauseMenu.h"

#include "Project_Hybria/Inventory/Inventory.h"

void UPauseMenu::OnUpKeyEvent()
{
	if (IsValid(FocusedInventory))
	{
		FocusedInventory->OnUpKeyEvent();
	}
}

void UPauseMenu::OnDownKeyEvent()
{
	if (IsValid(FocusedInventory))
	{
		FocusedInventory->OnDownKeyEvent();
	}
}

void UPauseMenu::OnRightKeyEvent()
{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("OnRightKeyEvent")));
	if (IsValid(FocusedInventory))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("caiu")));
		FocusedInventory->OnRightKeyEvent();
	}
}

void UPauseMenu::OnLeftKeyEvent()
{
	if (IsValid(FocusedInventory))
	{
		FocusedInventory->OnLeftKeyEvent();
	}
}
