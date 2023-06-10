#include "InventorySlot.h"

#include "Item.h"

void UInventorySlot::Set(TArray<UItem*> Items)
{
	for (const auto CurrItem : Items)
	{
		if (CurrItem->Name == ItemName)
		{
			bHasObject = true;
			break;
		}
	}
}
