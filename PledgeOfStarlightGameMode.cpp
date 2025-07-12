// Copyright Epic Games, Inc. All Rights Reserved.

#include "PledgeOfStarlightGameMode.h"
#include "PledgeOfStarlightCharacter.h"
#include "UObject/ConstructorHelpers.h"

APledgeOfStarlightGameMode::APledgeOfStarlightGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
