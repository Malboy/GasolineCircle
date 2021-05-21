// Copyright Epic Games, Inc. All Rights Reserved.

#include "GasolineCircleGameMode.h"
#include "GasolineCirclePlayerController.h"
#include "GasolineCircleCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGasolineCircleGameMode::AGasolineCircleGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AGasolineCirclePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Character/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}