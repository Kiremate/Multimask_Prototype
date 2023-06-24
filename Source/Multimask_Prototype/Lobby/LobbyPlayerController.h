#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPlayerController.generated.h"

class ULobbyUIWidget;

UCLASS()
class MULTIMASK_PROTOTYPE_API ALobbyPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    ALobbyPlayerController();

    virtual void BeginPlay() override;

    UFUNCTION(Server, Reliable, WithValidation)
        void Server_SetPlayerReady(bool bNewPlayerReady);
    bool Server_SetPlayerReady_Validate(bool bNewPlayerReady);
    void Server_SetPlayerReady_Implementation(bool bNewPlayerReady);

    UFUNCTION(BlueprintCallable, Category = "Lobby")
        void SetPlayerReady(bool bNewPlayerReady);

    UFUNCTION(BlueprintPure, Category = "Lobby")
        bool IsPlayerReady() const;

    virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Lobby")
        TSubclassOf<ULobbyUIWidget> LobbyUIWidgetClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lobby")
        ULobbyUIWidget* LobbyUIWidget;

    UPROPERTY(Replicated)
        bool bIsPlayerReady;

    void CreateLobbyWidget();
};
