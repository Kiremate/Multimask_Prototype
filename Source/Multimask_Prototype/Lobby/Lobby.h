#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Lobby.generated.h"

class ALobbyPlayerState;
class ULobbyUIWidget;

UCLASS()
class MULTIMASK_PROTOTYPE_API ULobby : public UObject
{
    GENERATED_BODY()

public:
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayersUpdated);

    UPROPERTY(BlueprintAssignable, Category = "Lobby")
        FOnPlayersUpdated OnPlayersUpdated;

    UFUNCTION(BlueprintCallable, Category = "Lobby")
        void JoinLobby(class ALobbyPlayerState* JoiningPlayer);

    UFUNCTION(BlueprintCallable, Category = "Lobby")
        void LeaveLobby(class ALobbyPlayerState* LeavingPlayer);

    UFUNCTION(BlueprintCallable, Category = "Lobby")
        void NotifyPlayerNamesUpdated();

    UFUNCTION(BlueprintCallable, Category = "Lobby")
        TArray<ALobbyPlayerState*> GetConnectedPlayers() const { return ConnectedPlayers; }
    
    void SetUIWidget(ULobbyUIWidget* Widget);
    void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
    UPROPERTY(ReplicatedUsing = OnRep_PlayerNames)
        TArray<FString> PlayerNames;

    UFUNCTION()
        void OnRep_PlayerNames();
private:
    UPROPERTY()
        TArray<ALobbyPlayerState*> ConnectedPlayers;

    UPROPERTY()
        ULobbyUIWidget* LobbyUIWidget;

    void GenerateRandomPlayerName(ALobbyPlayerState* PlayerState);
};
