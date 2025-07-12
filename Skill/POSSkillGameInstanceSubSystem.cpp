// Fill out your copyright notice in the Description page of Project Settings.


#include "POSSkillGameInstanceSubSystem.h"

UPOSSkillGameInstanceSubSystem::UPOSSkillGameInstanceSubSystem()
{
	LoadSkillDataTable();
	LoadUtilitySkillDataTable();
}

void UPOSSkillGameInstanceSubSystem::LoadSkillDataTable()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> TargetDataTable(TEXT("/Script/Engine.DataTable'/Game/PledgeOfStarlight/DataTable/DT_SKillDataTable.DT_SKillDataTable'"));
	if(TargetDataTable.Succeeded())
	{
		SkillDataTable = TargetDataTable.Object;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("SkillDataTable Load Failed"));
	}
	return;
}

void UPOSSkillGameInstanceSubSystem::LoadUtilitySkillDataTable()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> TargetDataTable(TEXT("/Script/Engine.DataTable'/Game/PledgeOfStarlight/DataTable/DT_UtilitySkillDataTable.DT_UtilitySkillDataTable'"));
	if(TargetDataTable.Succeeded())
	{
		UtilitySkillDataTable = TargetDataTable.Object;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Utility SkillDataTable Load Failed"));
	}
	return;
}

FSkillData UPOSSkillGameInstanceSubSystem::GetSkillDataFromTable(FName RowName)
{
	if(!SkillDataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("SkillDataTable nullptr"));
		return FSkillData();
	}

	FSkillData* SkillData = SkillDataTable->FindRow<FSkillData>(RowName,TEXT(""));

	if (SkillData)
	{
		return *SkillData;
	}

	UE_LOG(LogTemp, Warning, TEXT("SkillDatable can not find %s"), *RowName.ToString());
	return FSkillData();
}

FUtilitySkillData UPOSSkillGameInstanceSubSystem::GetUtilitySkillDataFromTable(FName RowName)
{
	if(!UtilitySkillDataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("Utility SkillDataTable nullptr"));
		return FUtilitySkillData();
	}

	FUtilitySkillData* UtilitySkillData = UtilitySkillDataTable->FindRow<FUtilitySkillData>(RowName,TEXT(""));

	if (UtilitySkillData)
	{
		return *UtilitySkillData;
	}

	UE_LOG(LogTemp, Warning, TEXT("Utility SkillDatable can not find %s"), *RowName.ToString());
	return FUtilitySkillData();
}

TMap<FName, FSkillMasterInfo> UPOSSkillGameInstanceSubSystem::GetEarnedSkillDataList()
{
	return EarnedSkillDataList;
}

void UPOSSkillGameInstanceSubSystem::AppendSkillEarnReadyData(FName SkillID)
{
	if(GetSkillDataFromTable(SkillID).Name == TEXT(""))
	{
		UE_LOG(LogTemp, Warning, TEXT("Skill ID Not Found, Skill Earn Ready cant'add %s"), *SkillID.ToString());
		return;
	}
	SkillEarnReadyStatus.Add(SkillID, 0);
}

void UPOSSkillGameInstanceSubSystem::AddEarnSkillData(const FName SkillID, const FSkillMasterInfo SkillData)
{
	EarnedSkillDataList.Add(SkillID, SkillData);
	return;
}

void UPOSSkillGameInstanceSubSystem::EarnSkillData(FName SkillID)
{
	FSkillMasterInfo SkillMasterInfo;
	SkillMasterInfo.EditableData.Level = 1;
	SkillMasterInfo.EditableData.LevelProgress = 0;
	SkillMasterInfo.MainSkillDataTable.DataTable = SkillDataTable;
	SkillMasterInfo.MainSkillDataTable.RowName = SkillID;

	switch (GetSkillDataFromTable(SkillID).SkillType)
	{
		case ESkillType::Utility:
			SkillMasterInfo.SubSkillDataTable.DataTable = UtilitySkillDataTable;
			SkillMasterInfo.SubSkillDataTable.RowName = SkillID;
			break;
		default:
			break;
	}
	
	AddEarnSkillData(SkillID, SkillMasterInfo);

	UE_LOG(LogTemp, Log, TEXT("Earn SkillData : %s"), *SkillID.ToString());
}

void UPOSSkillGameInstanceSubSystem::AddLevelProgressStatus(FName SkillID, float Amount)
{
	if(!EarnedSkillDataList.Contains(SkillID))
	{
		UE_LOG(LogTemp, Warning, TEXT("EarnSkillData Not Found"));
		return;
	}
	EarnedSkillDataList[SkillID].EditableData.LevelProgress += Amount;
	UE_LOG(LogTemp, Log, TEXT("SkillInProgressStatus %d 로 증가"),EarnedSkillDataList[SkillID].EditableData.LevelProgress);
	if(EarnedSkillDataList[SkillID].EditableData.LevelProgress >= 100)
	{
		EarnedSkillDataList[SkillID].EditableData.Level++;
		EarnedSkillDataList[SkillID].EditableData.LevelProgress = 0;
		UE_LOG(LogTemp, Log, TEXT("EarnSkillData Level Up : %s"), *SkillID.ToString());

	}
	return;
}

void UPOSSkillGameInstanceSubSystem::AddSkillEarnProgressStatus(FName SkillID, float Amount)
{
	if(!SkillEarnReadyStatus.Contains(SkillID))
	{
		UE_LOG(LogTemp, Warning, TEXT("SkillEarnReadyStatus Not Found"));
		return;
	}
	SkillEarnReadyStatus[SkillID] += Amount;
	UE_LOG(LogTemp, Log, TEXT("SkillEarnReadyStatus %f 로 증가"), SkillEarnReadyStatus[SkillID]);
	if(SkillEarnReadyStatus[SkillID] >= 100)
	{
		if(EarnedSkillDataList.Contains(SkillID))
		{
			UE_LOG(LogTemp, Warning, TEXT("SkillData Already Exist : %s"), *SkillID.ToString());
		}
		
		EarnSkillData(SkillID);
		SkillEarnReadyStatus.Remove(SkillID);
	}
	return;
}
