// Fill out your copyright notice in the Description page of Project Settings.


#include "POSQuestSingleSlot.h"
#include "POSQuestTypePanelWidget.h"
#include "POSQuestMainPanelWidget.h"

void UPOSQuestSingleSlot::NativeConstruct()
{
	Super::NativeConstruct();
	if (QuestButton)
	{
		QuestButton->OnClicked.AddDynamic(this, &UPOSQuestSingleSlot::OnQuestButtonClicked);
	}
	QuestText->SetText(QuestInfo.Title);
}

void UPOSQuestSingleSlot::OnQuestButtonClicked()
{
	if(!QuestTypePanelUserWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("QuestTypePanelWidget is nullptr"));	
		return;
	}
	UPOSQuestTypePanelWidget* QuestTypePanelWidget = Cast<UPOSQuestTypePanelWidget>(QuestTypePanelUserWidget);
	if(!QuestTypePanelWidget->QuestMainPanelWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("QuestMainPanelWidget is nullptr"));	
		return;
	}
	QuestTypePanelWidget->QuestMainPanelWidget->SetInfomation(QuestInfo);
}
