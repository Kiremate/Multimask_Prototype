#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LobbyBlueprintLibrary.generated.h"

class ULobby;

UCLASS()
class MULTIMASK_PROTOTYPE_API ULobbyBlueprintLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Lobby")
        static TArray<class ALobbyPlayerState*> GetConnectedPlayers(ULobby* Lobby);
};
