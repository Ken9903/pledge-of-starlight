// Fill out your copyright notice in the Description page of Project Settings.


#include "POSQuestTypePanelWidget.h"
#include "PledgeOfStarlight/Quest/POSQuestGameInstanceSubSystem.h"

void UPOSQuestTypePanelWidget::SetUpQuestUI()
{
	UPOSQuestGameInstanceSubSystem* QuestGameInstanceSubSystem = GetGameInstance()->GetSubsystem<UPOSQuestGameInstanceSubSystem>();
	if(QuestGameInstanceSubSystem)
	{
		TSet<FName> TargetNameList;
		switch (QuestPanelType)
		{
			case EPOSQuestProgressType::StartAble:
				TargetNameList = QuestGameInstanceSubSystem->GetStartAbleList();
				break;
			case EPOSQuestProgressType::InProgress:
				TargetNameList = QuestGameInstanceSubSystem->GetInProgressList();
				break;
			case EPOSQuestProgressType::Completed:
				TargetNameList = QuestGameInstanceSubSystem->GetCompletedListList();
				break;
			default:
				TargetNameList = QuestGameInstanceSubSystem->GetStartAbleList();
				UE_LOG(LogTemp, Warning, TEXT("EPOSQuestProgressType Error"));
				break;
		}

		for (auto TargetName : TargetNameList)
		{
			QuestSingleSlotInstance = CreateWidget<UPOSQuestSingleSlot>(GetOwningPlayer(), WBP_POSQuestSingleSlotClass);
			QuestSingleSlotInstance->QuestInfo = QuestGameInstanceSubSystem->GetQuestData(TargetName);
			QuestSingleSlotInstance->QuestTypePanelUserWidget = this; // 참조를 위해 본인을 넘겨줌.
			QuestScrollBox->AddChild(QuestSingleSlotInstance);
		}
	}

	return;
}
