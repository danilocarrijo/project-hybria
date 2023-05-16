#pragma once

UENUM(BlueprintType) // Essa linha torna a enumeração disponível para ser usada em Blueprints
enum class ECharacterMovement : uint8
{
    Walk UMETA(DisplayName = "Walk"),
    Climbing UMETA(DisplayName = "Clibing"),
    LadderClimbing UMETA(DisplayName = "Ladder Clibing"),
    Swimming UMETA(DisplayName = "Swimming"),
    Diving UMETA(DisplayName = "Diving")
};