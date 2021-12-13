// Copyright Epic Games, Inc. All Rights Reserved.

#include "SpaceGameMode.h"
#include "MyPlayer.h"

ASpaceGameMode::ASpaceGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AMyPlayer::StaticClass();
}

