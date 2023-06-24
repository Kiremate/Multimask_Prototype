// Copyright Epic Games, Inc. All Rights Reserved.

#include "Multimask_PrototypeGameMode.h"
#include "Multimask_PrototypeCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMultimask_PrototypeGameMode::AMultimask_PrototypeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
