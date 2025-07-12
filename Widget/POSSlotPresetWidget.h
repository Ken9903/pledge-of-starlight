// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PledgeOfStarlight/Struct/POSSlotData.h"
#include "POSSlotPresetWidget.generated.h"

/**
 * 
 */
UCLASS()
class PLEDGEOFSTARLIGHT_API UPOSSlotPresetWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(Category = "POS|Widget", BlueprintImplementableEvent , BlueprintCallable)
	void SetPresetData(const TArray<FSlotData> &PresetDatas);
};
