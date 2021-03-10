// Copyright Epic Games, Inc. All Rights Reserved.

#include "NeoNinjaGameMode.h"
#include "NeoNinjaCharacter.h"
#include "UObject/ConstructorHelpers.h"

ANeoNinjaGameMode::ANeoNinjaGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
