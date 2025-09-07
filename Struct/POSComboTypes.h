// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "POSComboTypes.generated.h"

UENUM()
enum class EPOSComboState : uint8
{
	Idle,
	Playing,
	Buffering
};

// No step struct: combo timing and names are defined in the Primary Asset.


