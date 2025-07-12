// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "POSConsumableItem.h"
#include "POSBasicMPPotion.generated.h"

/**
 * 
 */
UCLASS()
class PLEDGEOFSTARLIGHT_API APOSBasicMPPotion : public APOSConsumableItem
{
	GENERATED_BODY()

	APOSBasicMPPotion();

public:
	void UseItem() override;
};
