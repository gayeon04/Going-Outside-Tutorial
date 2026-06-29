// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "test_GameMode.generated.h"

/**
 *  Simple GameMode for a third person game
 */
UCLASS(abstract)
class Atest_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	/** Constructor */
	Atest_GameMode();
};



