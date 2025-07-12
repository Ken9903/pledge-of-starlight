// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PledgeOfStarlight/Struct/POSSkillMasterInfo.h"
#include "POSSkillSingleSlotWidget.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonDown, FSkillMasterInfo, EventValue);

UCLASS()
class PLEDGEOFSTARLIGHT_API UPOSSkillSingleSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnButtonDown OnButtonDown;
	
protected:
	UFUNCTION(BlueprintCallable)
	void TriggerButtonDownEvent(FSkillMasterInfo SkillMasterInfo);
	
};
