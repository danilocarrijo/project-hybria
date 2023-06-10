#include "Inventory.h"

#include "InventorySlot.h"
#include "Potion.h"

void UInventory::OnUpKeyEvent_Implementation()
{
}

void UInventory::OnDownKeyEvent_Implementation()
{
}

void UInventory::OnRightKeyEvent_Implementation()
{
}

void UInventory::OnLeftKeyEvent_Implementation()
{
}

void UInventory::SetSlots()
{
	UPotion* HealthPortion = NewObject<UPotion>();
	HealthPortion->Name = "HealthPortion";
	Items.Add(HealthPortion);
	
	for (const auto CurrSlot : Slots)
	{
		CurrSlot->Set(Items);
	}
}
