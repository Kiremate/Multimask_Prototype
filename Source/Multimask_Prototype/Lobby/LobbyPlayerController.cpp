#include "LobbyPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "LobbyUIWidget.h" 
#include "Net/UnrealNetwork.h"


ALobbyPlayerController::ALobbyPlayerController()
    : Super()
    , bIsPlayerReady(false)
{
    LobbyUIWidgetClass = LoadClass<ULobbyUIWidget>(nullptr, TEXT("/Game/Blueprints/Widgets/LobbyWidgetBlueprint.LobbyWidgetBlueprint_C"));
}

void ALobbyPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (IsLocalController())
    {
        CreateLobbyWidget();
    }
}

void ALobbyPlayerController::Server_SetPlayerReady_Implementation(bool bNewPlayerReady)
{
    bIsPlayerReady = bNewPlayerReady;
}

bool ALobbyPlayerController::Server_SetPlayerReady_Validate(bool bNewPlayerReady)
{
    return true;
}

void ALobbyPlayerController::SetPlayerReady(bool bNewPlayerReady)
{
    if (IsLocalController())
    {
        Server_SetPlayerReady(bNewPlayerReady);
    }
}

bool ALobbyPlayerController::IsPlayerReady() const
{
    return bIsPlayerReady;
}

void ALobbyPlayerController::CreateLobbyWidget()
{
    // Assuming you have assigned the LobbyUIWidgetClass in the Blueprint defaults
    if (LobbyUIWidgetClass)
    {
        LobbyUIWidget = CreateWidget<ULobbyUIWidget>(this, LobbyUIWidgetClass);
        if (LobbyUIWidget)
        {
            LobbyUIWidget->AddToViewport();
            UE_LOG(LogTemp, Warning, TEXT("Widget created and added to viewport"));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Widget creation failed"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("LobbyUIWidgetClass not set"));
    }
}


void ALobbyPlayerController::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ALobbyPlayerController, bIsPlayerReady);
}
