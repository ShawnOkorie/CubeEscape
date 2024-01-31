// Copyright Epic Games, Inc. All Rights Reserved.

#include "HelloCppGameMode.h"
#include "HelloCppCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHelloCppGameMode::AHelloCppGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
