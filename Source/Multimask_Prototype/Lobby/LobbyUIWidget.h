#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Lobby.h"
#include "LobbyUIWidget.generated.h"
UCLASS()
class MULTIMASK_PROTOTYPE_API ULobbyUIWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Lobby")
        void SetLobby(class ULobby* InLobby);
    // This function will be bound to the delegate and will be called when players get updated
    UFUNCTION()
        void OnPlayersUpdated();
    UFUNCTION(BlueprintCallable, Category = "Lobby")
        void UpdatePlayerNames();
    UFUNCTION(BlueprintImplementableEvent, Category = "Lobby")
        void BlueprintEvent_UpdatePlayerNames(const TArray<FString>& PlayerNames);

protected:
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
        class UWrapBox* PlayerNamesWrapBox;
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
        class UTextBlock* PlayerCountTextBlock;
    // The Lobby variable declaration
    class ULobby* Lobby;

};
