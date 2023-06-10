#pragma once

UENUM(BlueprintType)
enum class EInventoryType : uint8
{
	Potion UMETA(DisplayName = "Potion"),
	Sword UMETA(DisplayName = "Sword"),
	Shield UMETA(DisplayName = "Shield"),
	QuestItem UMETA(DisplayName = "QuestItem"),
	Item UMETA(DisplayName = "Item"),
	PowerUp UMETA(DisplayName = "PowerUp")
};