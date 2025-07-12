// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "POSQuestMainPanelWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "PledgeOfStarlight/Struct/POSQuestInfo.h"
#include "POSQuestSingleSlot.generated.h"

/**
 * 
 */
UCLASS()
class PLEDGEOFSTARLIGHT_API UPOSQuestSingleSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = "POS|Quest", VisibleAnywhere, BlueprintReadWrite)
	FPOSQuestInfo QuestInfo;

	UPROPERTY(Category = "POS|Widget", BlueprintReadWrite)
	TObjectPtr<UUserWidget> QuestTypePanelUserWidget; //댕글링 문제 회피를 위해 헤더파일을 옮기기 위함.

protected:
	UPROPERTY(Category = "POS|Widget", EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> QuestButton;

	UPROPERTY(Category = "POS|Widget", EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> QuestText;

	UPROPERTY(Category = "POS|Widget", VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UPOSQuestMainPanelWidget> QuestMainPanelWidget;

	void NativeConstruct() override;
private:
	UFUNCTION(Category = "POS|Widget")
	void OnQuestButtonClicked();
	
};
