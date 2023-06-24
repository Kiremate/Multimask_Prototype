// Lobby.cpp

#include "Lobby.h"
#include "LobbyPlayerState.h"
#include "LobbyUIWidget.h"
#include "Net/UnrealNetwork.h"

void ULobby::JoinLobby(class ALobbyPlayerState* JoiningPlayer)
{
    if (IsValid(JoiningPlayer) && !ConnectedPlayers.Contains(JoiningPlayer)) {
        if (JoiningPlayer && !ConnectedPlayers.Contains(JoiningPlayer))
        {
            ConnectedPlayers.Add(JoiningPlayer);
            UE_LOG(LogTemp, Warning, TEXT("Player has joined the lobby. Number of connected players: %d"), ConnectedPlayers.Num());

            GenerateRandomPlayerName(JoiningPlayer);

            for (const ALobbyPlayerState* PlayerState : ConnectedPlayers)
            {
                PlayerNames.Add(PlayerState->GetPlayerName());
            }
            NotifyPlayerNamesUpdated();
            // Call the delegate
            OnPlayersUpdated.Broadcast();
        }
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("We fucked up JoiningPlayer is not valid"));
    }
    
}


void ULobby::LeaveLobby(class ALobbyPlayerState* LeavingPlayer)
{
    if (LeavingPlayer)
    {
        ConnectedPlayers.Remove(LeavingPlayer);

        for (const ALobbyPlayerState* PlayerState : ConnectedPlayers)
        {
            PlayerNames.Remove(LeavingPlayer->GetPlayerName());
        }
        NotifyPlayerNamesUpdated();
        // Call the delegate
        OnPlayersUpdated.Broadcast();
    }
}

void ULobby::NotifyPlayerNamesUpdated()
{
    if (LobbyUIWidget)
    {
        LobbyUIWidget->UpdatePlayerNames();
    }
}

void ULobby::GenerateRandomPlayerName(ALobbyPlayerState* PlayerState)
{
    if (PlayerState)
    {
        PlayerState->GenerateRandomPlayerName();
    }
}

void ULobby::SetUIWidget(ULobbyUIWidget* Widget)
{
    LobbyUIWidget = Widget;
}

void ULobby::OnRep_PlayerNames()
{
    // This function is automatically called on clients whenever PlayerNames changes.
    // Here you would update your local UI widget to reflect the new player names.
    NotifyPlayerNamesUpdated();
}

void ULobby::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ULobby, PlayerNames);
}
