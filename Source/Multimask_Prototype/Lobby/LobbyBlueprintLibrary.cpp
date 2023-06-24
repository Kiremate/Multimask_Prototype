#include "LobbyBlueprintLibrary.h"
#include "Lobby.h"

TArray<class ALobbyPlayerState*> ULobbyBlueprintLibrary::GetConnectedPlayers(ULobby* Lobby)
{
    if (Lobby)
    {
        return Lobby->GetConnectedPlayers();
    }
    return TArray<class ALobbyPlayerState*>();
}
