#pragma once

UENUM(BlueprintType) // Essa linha torna a enumeração disponível para ser usada em Blueprints
enum class ECharacterMovement : uint8
{
    Walk UMETA(DisplayName = "Walk"),
    Clibing UMETA(DisplayName = "Clibing"),
    LadderClibing UMETA(DisplayName = "Ladder Clibing"),
    Swimming UMETA(DisplayName = "Swimming")
};