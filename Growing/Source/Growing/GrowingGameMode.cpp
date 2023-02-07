// Copyright Epic Games, Inc. All Rights Reserved.

#include "GrowingGameMode.h"
#include "GrowingCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGrowingGameMode::AGrowingGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
