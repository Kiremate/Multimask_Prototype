// LobbyPlayerState.cpp

#include "LobbyPlayerState.h"
#include <Multimask_Prototype/LobbyGameMode.h>
#include "LobbyPlayerState.h"
#include "Net/UnrealNetwork.h"
ALobbyPlayerState::ALobbyPlayerState()
{
    PlayerName = TEXT("");
}

void ALobbyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ALobbyPlayerState, PlayerName);
}

FString ALobbyPlayerState::GetPlayerName() const
{
    if (this == nullptr)
    {
        return TEXT("DefaultPlayerName");
    }
    else
    {
        return PlayerName;
    }
}

void ALobbyPlayerState::GenerateRandomPlayerName()
{
    TArray<FString> PlayerNames;
    PlayerNames.Add(TEXT("John"));
    PlayerNames.Add(TEXT("Jane"));
    PlayerNames.Add(TEXT("Alex"));

    int32 RandomIndex = FMath::RandRange(0, PlayerNames.Num() - 1);

    PlayerName = PlayerNames[RandomIndex];

    UE_LOG(LogTemp, Warning, TEXT("Random Player Name: %s"), *PlayerName);
}
