// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Tp1GameMode.generated.h"

/**
 *  Simple GameMode for a third person game
 */
UCLASS(abstract)
class ATp1GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	/** Constructor */
	ATp1GameMode();
};



