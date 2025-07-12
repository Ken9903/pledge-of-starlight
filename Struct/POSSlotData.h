// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "POSItemMasterInfo.h"
#include "POSSkillMasterInfo.h"
#include "PledgeOfStarlight/Enum/POSSlotType.h"
#include "POSSlotData.Generated.h"

USTRUCT(BlueprintType)
struct FSlotData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = "POS|Slot", EditAnywhere, BlueprintReadWrite)
	ESlotType SlotType;

	UPROPERTY(Category = "POS|Slot", EditAnywhere, BlueprintReadWrite)
	FSkillMasterInfo SkillMasterInfo;
	
	UPROPERTY(Category = "POS|Slot", EditAnywhere, BlueprintReadWrite)
	FItemMasterInfo ItemMasterInfo;
	
};
