#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "./Lobby/Lobby.h"
#include "LobbyGameMode.generated.h"

UCLASS()
class MULTIMASK_PROTOTYPE_API ALobbyGameMode : public AGameMode
{
    GENERATED_BODY()

public:
    ALobbyGameMode(const FObjectInitializer& ObjectInitializer);

    virtual void BeginPlay() override;

    virtual void PostLogin(APlayerController* NewPlayer) override;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
        TSubclassOf<class ULobbyUIWidget> LobbyUIWidgetClass;
    void UpdateConnectedPlayers();
private:
    UPROPERTY()
    ULobby* Lobby;
    UPROPERTY()
        class ULobbyUIWidget* LobbyUIWidget;
};
