// Copyright Epic Games, Inc. All Rights Reserved.

#include "ZeldaBOTWGameMode.h"
#include "ZeldaBOTWCharacter.h"
#include "UObject/ConstructorHelpers.h"

AZeldaBOTWGameMode::AZeldaBOTWGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
