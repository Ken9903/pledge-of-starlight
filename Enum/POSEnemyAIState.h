// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "POSEnemyAIState.generated.h"

UENUM(BlueprintType)
enum class EEnemyAIState : uint8
{
	Patrol		UMETA(DisplayName = "Patrol"),
	Chase		UMETA(DisplayName = "Chase"),
	Attack		UMETA(DisplayName = "Attack"),
	Hit			UMETA(DisplayName = "Hit"),
	Dead		UMETA(DisplayName = "Dead")
};

