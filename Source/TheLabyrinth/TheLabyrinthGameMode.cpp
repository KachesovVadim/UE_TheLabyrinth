// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheLabyrinthGameMode.h"
#include "TheLabyrinthCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATheLabyrinthGameMode::ATheLabyrinthGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
