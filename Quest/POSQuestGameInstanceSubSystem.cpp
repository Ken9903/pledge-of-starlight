// Fill out your copyright notice in the Description page of Project Settings.


#include "POSQuestGameInstanceSubSystem.h"

#include "PledgeOfStarlight/Enum/POSQuestProgressType.h"
#include "PledgeOfStarlight/Struct/POSQuestInfo.h"

UPOSQuestGameInstanceSubSystem::UPOSQuestGameInstanceSubSystem()
{
	LoadQuestDataTable();
}

FPOSQuestInfo UPOSQuestGameInstanceSubSystem::GetQuestData(FName QuestID)
{
	if(!QuestDataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("Quest DataTable nullptr"));
		return FPOSQuestInfo();
	}
	
	FPOSQuestInfo* QuestInfo = QuestDataTable->FindRow<FPOSQuestInfo>(QuestID, TEXT(""));
	if(QuestInfo)
	{
		return *QuestInfo;
	}

	UE_LOG(LogTemp, Warning, TEXT("Quest Datable can not find %s"), *QuestID.ToString());
	return FPOSQuestInfo();
}

EPOSQuestProgressType UPOSQuestGameInstanceSubSystem::FindQuestStatus(FName QuestID)
{
	if(InAccessibleList.Contains(QuestID))
	{
		return EPOSQuestProgressType::InAccessible;
	}
	if(StartAbleList.Contains(QuestID))
	{
		return EPOSQuestProgressType::StartAble;
	}
	if(InProgressList.Contains(QuestID))
	{
		return EPOSQuestProgressType::InProgress;
	}
	if(CompletedList.Contains(QuestID))
	{
		return EPOSQuestProgressType::Completed;
	}

	UE_LOG(LogTemp, Warning, TEXT("Can't find QuestList Status"))
	return EPOSQuestProgressType::InAccessible;
}

TSet<FName> UPOSQuestGameInstanceSubSystem::GetStartAbleList()
{
	return StartAbleList;
}

TSet<FName> UPOSQuestGameInstanceSubSystem::GetCompletedListList()
{
	return CompletedList;
}

TSet<FName> UPOSQuestGameInstanceSubSystem::GetInProgressList()
{
	return InProgressList;
}

int32 UPOSQuestGameInstanceSubSystem::GetInProgressStatus(FName QuestID)
{
	if(InProgressStatus.Contains(QuestID))
	{
		return InProgressStatus[QuestID];
	}
	UE_LOG(LogTemp, Warning, TEXT("InProgressList에 존재하지않는 QuestID"));
	return 0;
}

void UPOSQuestGameInstanceSubSystem::AddInProgressStatus(FName QuestID, int32 Amount)
{
	if(InProgressStatus.Contains(QuestID))
	{
		InProgressStatus[QuestID] = InProgressStatus[QuestID] + Amount;
		UE_LOG(LogTemp, Log, TEXT("InProgressStatus %d 로 증가"),InProgressStatus[QuestID]);

		//TODO : ClearCheck. 필요한 경우에 실시.
		/*if(GetQuestData(QuestID).QuestDetailTableHandler.GetRow<>())*/
		
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("InProgressList에 존재하지않는 QuestID"));
	return;
}

void UPOSQuestGameInstanceSubSystem::AppendInAccessibleQuest(FName QuestID)
{
	if(InAccessibleList.Contains((QuestID)))
	{
		return;
	}
	InAccessibleList.Add(QuestID);
	return;
}

void UPOSQuestGameInstanceSubSystem::AppendStartAbleQuest(FName QuestID)
{
	if(!InAccessibleList.Contains(QuestID) && StartAbleList.Contains(QuestID))
	{
		return;
	}
	InAccessibleList.Remove(QuestID);
	StartAbleList.Add(QuestID);
	return;
}

void UPOSQuestGameInstanceSubSystem::AppendInProgressQuest(FName QuestID)
{
	if(!StartAbleList.Contains(QuestID) || InProgressList.Contains(QuestID)) //전 단계 리스트에 없거나, 이미 추가가 되어있는 경우
	{
		return;
	}
	StartAbleList.Remove(QuestID);
	InProgressList.Add(QuestID);
	InProgressStatus.Add(QuestID, 0); //진행 상태 저장용.
	return;
}


void UPOSQuestGameInstanceSubSystem::AppendCompletedQuest(FName QuestID)
{
	if(!InProgressList.Contains(QuestID) || CompletedList.Contains(QuestID)) //전 단계 리스트에 없거나, 이미 추가가 되어있는 경우
	{
		return;
	}
	InProgressList.Remove(QuestID);
	CompletedList.Add(QuestID);
	return;
}

void UPOSQuestGameInstanceSubSystem::LoadQuestDataTable()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> TargetDataTable(TEXT("/Script/Engine.DataTable'/Game/PledgeOfStarlight/DataTable/DT_QuestDataTable.DT_QuestDataTable'"));
	if(TargetDataTable.Succeeded())
	{
		QuestDataTable = TargetDataTable.Object;
		InitQuestStatus();  //모든 퀘스트 정보 InAccessible로 초기화
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Quest Data Table Load Failed"));
	}
	return;
}

void UPOSQuestGameInstanceSubSystem::InitQuestStatus()
{
	if(!QuestDataTable)
	{
		UE_LOG(LogTemp, Log, TEXT("Quest Data Table Load Failed"));
		return;
	}

	TArray<FName> RowNames = QuestDataTable->GetRowNames();
	for (const FName& RowName : RowNames)
	{
		AppendInAccessibleQuest(RowName);
	}
	return;
}
