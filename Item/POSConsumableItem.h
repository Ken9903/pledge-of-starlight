// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "POSItemBase.h"
#include "PledgeOfStarlight/Struct/POSConsumableItemData.h"
#include "POSConsumableItem.generated.h"

/**
 * 
 */
UCLASS()
class PLEDGEOFSTARLIGHT_API APOSConsumableItem : public APOSItemBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(Category = "POS|Item", VisibleAnywhere)
	FConsumableItemData ConsumableItemData;
	
};
