// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "NetJamGameMode.h"
#include "NetJamCharacter.h"
#include "UObject/ConstructorHelpers.h"

ANetJamGameMode::ANetJamGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/TPCPlayer"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
