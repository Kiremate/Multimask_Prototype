// LobbyPlayerState.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "LobbyPlayerState.generated.h"

UCLASS()
class MULTIMASK_PROTOTYPE_API ALobbyPlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    ALobbyPlayerState();

    FString GetPlayerName() const;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UFUNCTION(BlueprintCallable, Category = "Lobby")
        void GenerateRandomPlayerName();

private:
    UPROPERTY(Replicated)
        FString PlayerName;
};
