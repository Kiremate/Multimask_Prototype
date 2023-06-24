#include "LobbyUIWidget.h"
#include "Components/WrapBox.h"
#include "Components/TextBlock.h"
#include "UMG.h"
#include "LobbyPlayerState.h"


void ULobbyUIWidget::UpdatePlayerNames()
{
    TArray<ALobbyPlayerState*> ConnectedPlayers;
    if (Lobby)
    {
        ConnectedPlayers = Lobby->GetConnectedPlayers();
        UE_LOG(LogTemp, Warning, TEXT("Got connected players: %d"), ConnectedPlayers.Num());
    }

    if (PlayerNamesWrapBox)
    {
        PlayerNamesWrapBox->ClearChildren();

        for (ALobbyPlayerState* PlayerState : ConnectedPlayers)
        {
            if (PlayerState) // Check if PlayerState is valid
            {
                FString PlayerName = PlayerState->GetPlayerName();
                UTextBlock* TextBlock = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
                if (TextBlock)
                {
                    TextBlock->SetText(FText::FromString(PlayerName));
                    PlayerNamesWrapBox->AddChild(TextBlock);
                    UE_LOG(LogTemp, Warning, TEXT("Added player name: %s"), *PlayerName);
                }
                else
                {
                    UE_LOG(LogTemp, Error, TEXT("Failed to construct UTextBlock."));
                }
            }
        }

    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("PlayerNamesWrapBox is null."));
    }

    // Update player count text
    if (PlayerCountTextBlock)
    {
        FString PlayerCountString = FString::Printf(TEXT("Player Count: %d"), ConnectedPlayers.Num());
        PlayerCountTextBlock->SetText(FText::FromString(PlayerCountString));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("PlayerCountTextBlock is null."));
    }
}

void ULobbyUIWidget::SetLobby(ULobby* InLobby)
{
    // Set the lobby reference
    Lobby = InLobby;
    if (Lobby)
    {
        // Bind the OnPlayersUpdated function to the delegate
        Lobby->OnPlayersUpdated.AddDynamic(this, &ULobbyUIWidget::OnPlayersUpdated);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to set Lobby."));
    }
}

void ULobbyUIWidget::OnPlayersUpdated()
{
    // This function will be called when the OnPlayersUpdated delegate is broadcasted
    UpdatePlayerNames();
}

