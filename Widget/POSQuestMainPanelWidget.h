// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PledgeOfStarlight/Struct/POSQuestInfo.h"
#include "POSQuestMainPanelWidget.generated.h"

/**
 * 
 */
UCLASS()
class PLEDGEOFSTARLIGHT_API UPOSQuestMainPanelWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(Category = "POS|Quest", BlueprintImplementableEvent, BlueprintCallable)
	void SetInfomation(FPOSQuestInfo QuestInfo);
	
};
