// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PledgeOfStarlight/Struct/POSSkillMasterInfo.h"
#include "PledgeOfStarlight/Struct/POSSlotData.h"
#include "POSSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PLEDGEOFSTARLIGHT_API UPOSSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = "POS|Save", EditDefaultsOnly)
	TMap<FName, FSkillMasterInfo> EarnedSkillDataList;

	UPROPERTY(Category = "POS|Save", EditDefaultsOnly)
	TArray<FSlotData> PresetDataList;

	UPROPERTY(Category = "POS|Save", EditDefaultsOnly)
	TArray<FItemMasterInfo> InventoryDataList;
	
};
