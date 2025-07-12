// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "PledgeOfStarlight/Enum/POSItemType.h"
#include "PledgeOfStarlight/Struct/POSItemMasterInfo.h"
#include "POSItemTypePanelWidget.generated.h"

/**
 * 
 */
UCLASS()
class PLEDGEOFSTARLIGHT_API UPOSItemTypePanelWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = "POS|Widget", EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UScrollBox> ItemListSizeBox;
	
	UPROPERTY(Category = "POS|Widget", EditInstanceOnly, BlueprintReadWrite, meta = (ExposeOnSpawn))
	EItemType ItemPanelType;

	UPROPERTY(Category = "POS|Widget", EditDefaultsOnly)
	int32 MaxHorizontalItemAmount = 7;

	UPROPERTY(Category = "POS|Widget", VisibleDefaultsOnly)
	int32 CurrentHorizontalItemAmount = 0;

	UPROPERTY(Category = "POS|Widget", EditDefaultsOnly)
	TSubclassOf<UUserWidget> WBP_MenuSlot;

	UPROPERTY(Category = "POS|Widget", EditDefaultsOnly)
	TSubclassOf<UUserWidget> WBP_POSItemSingleSlot;
	
	UFUNCTION(Category = "POS|Item", BlueprintCallable)
	void SetUpItemUI();

private:
	UFUNCTION(Category = "POS|Item")
	bool CheckSameItemTypePanel(FItemMasterInfo ItemMasterInfo);

	UPROPERTY(Category = "POS|Widget", VisibleDefaultsOnly)
	TObjectPtr<UUserWidget> MenuSlotLineInstance;
	
};
