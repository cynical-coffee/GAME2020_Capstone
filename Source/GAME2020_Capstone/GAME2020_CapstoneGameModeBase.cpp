// Copyright Epic Games, Inc. All Rights Reserved.


#include "GAME2020_CapstoneGameModeBase.h"

#include "Player_Character.h"

AGAME2020_CapstoneGameModeBase::AGAME2020_CapstoneGameModeBase()
{
	DefaultPawnClass = APlayer_Character::StaticClass();
}
