// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "POSConsumableItem.h"
#include "POSBasicHPPotion.generated.h"

/**
 * 
 */
UCLASS()
class PLEDGEOFSTARLIGHT_API APOSBasicHPPotion : public APOSConsumableItem
{
	GENERATED_BODY()

	APOSBasicHPPotion();

public:
	void UseItem() override;
	
};
