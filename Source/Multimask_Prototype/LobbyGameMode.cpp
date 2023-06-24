#include "LobbyGameMode.h"
#include "Lobby/LobbyPlayerState.h"
#include "Lobby/LobbyBlueprintLibrary.h"
#include "Lobby/LobbyPlayerController.h"

ALobbyGameMode::ALobbyGameMode(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    // Create a new Lobby instance when the game starts
    Lobby = ObjectInitializer.CreateDefaultSubobject<ULobby>(this, TEXT("Lobby"));
    PlayerStateClass = ALobbyPlayerState::StaticClass();
    PlayerControllerClass = ALobbyPlayerController::StaticClass();
}


void ALobbyGameMode::BeginPlay()
{
    Super::BeginPlay();

    UpdateConnectedPlayers();
}

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);
    UE_LOG(LogTemp, Warning, TEXT("PostLogin called"));

    if (NewPlayer) // Check if NewPlayer is valid
    {
        ALobbyPlayerState* NewPlayerState = Cast<ALobbyPlayerState>(NewPlayer->PlayerState);
        if (NewPlayerState)
        {
            // Make sure to call this on the server so PlayerNames gets replicated to clients.
            if (GetWorld()->GetNetMode() == NM_DedicatedServer || GetWorld()->GetNetMode() == NM_ListenServer)
            {
                Lobby->JoinLobby(NewPlayerState);
            }
            UE_LOG(LogTemp, Warning, TEXT("Player has joined the lobby"));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("NewPlayerState is not of ALobbyPlayerState type."));
        }
    }
}

void ALobbyGameMode::UpdateConnectedPlayers()
{
    // Fetch all player states
    for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
    {
        APlayerController* PlayerController = Iterator->Get();
        ALobbyPlayerState* PlayerState = Cast<ALobbyPlayerState>(PlayerController->PlayerState);

        if (PlayerState != nullptr)
        {
            Lobby->JoinLobby(PlayerState);
        }
    }
}