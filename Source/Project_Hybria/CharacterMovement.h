#pragma once

UENUM(BlueprintType) // Essa linha torna a enumeração disponível para ser usada em Blueprints
enum class ECharacterMovement : uint8
{
    Walk UMETA(DisplayName = "Walk"), // O UMETA define o nome que será exibido no Blueprint para esse valor
    Clibing UMETA(DisplayName = "Clibing")
};