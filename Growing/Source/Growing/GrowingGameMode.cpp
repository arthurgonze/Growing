// Copyright Epic Games, Inc. All Rights Reserved.

#include "GrowingGameMode.h"
#include "GrowingCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGrowingGameMode::AGrowingGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Content/GrowingCustomContent/Characters/BP_FP_Character"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
