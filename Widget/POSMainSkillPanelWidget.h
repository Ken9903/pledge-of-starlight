// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PledgeOfStarlight/Struct/POSSkillMasterInfo.h"
#include "Components/ScrollBox.h"
#include "POSMainSkillPanelWidget.generated.h"

/**
 * 
 */
UCLASS()
class PLEDGEOFSTARLIGHT_API UPOSMainSkillPanelWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Category = "POS|Widget", EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UScrollBox> SkillListSizeBox;

	UPROPERTY(Category = "POS|Widget", EditDefaultsOnly)
	int32 MaxHorizontalSkillAmount = 3;

	UPROPERTY(Category = "POS|Widget", VisibleDefaultsOnly)
	int32 CurrentHorizontalSkillAmount = 0;

	UPROPERTY(Category = "POS|Widget", EditDefaultsOnly)
	TSubclassOf<UUserWidget> WBP_MenuSlot;

	UPROPERTY(Category = "POS|Widget", EditDefaultsOnly)
	TSubclassOf<UUserWidget> WBP_POSSkillSingleSlot;

	UPROPERTY(Category = "POS|Widget", EditDefaultsOnly, BlueprintReadOnly)
	TMap<FName, FSkillMasterInfo> EarnedSkillData;

	UFUNCTION(Category = "POS|Skill", BlueprintCallable)
	void SetUpSkillUI();

	UFUNCTION(Category = "POS|Widget", BlueprintImplementableEvent , BlueprintCallable)
	void SetInfoSKillSlotButtonDown(FSkillMasterInfo SkillData);

private:
	UPROPERTY(Category = "POS|Widget", VisibleDefaultsOnly)
	TObjectPtr<UUserWidget> MenuSlotLineInstance;
};
