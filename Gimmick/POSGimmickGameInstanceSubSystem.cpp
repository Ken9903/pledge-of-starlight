// Fill out your copyright notice in the Description page of Project Settings.


#include "POSGimmickGameInstanceSubSystem.h"

UPOSGimmickGameInstanceSubSystem::UPOSGimmickGameInstanceSubSystem()
{
	LoadGimmickObjectDataTable();
}

FPOSGimmickObjectInfo UPOSGimmickGameInstanceSubSystem::GetGimmickObjectData(FName GimmickObjectID)
{
	if(!GimmickObjectDataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("GimmickObject DataTable nullptr"));
		return FPOSGimmickObjectInfo();
	}
	
	FPOSGimmickObjectInfo* GimmickObjectInfo = GimmickObjectDataTable->FindRow<FPOSGimmickObjectInfo>(GimmickObjectID, TEXT(""));
	if(GimmickObjectInfo)
	{
		return *GimmickObjectInfo;
	}

	UE_LOG(LogTemp, Warning, TEXT("GimmickObject Datable can not find %s"), *GimmickObjectID.ToString());
	return FPOSGimmickObjectInfo();
}

void UPOSGimmickGameInstanceSubSystem::LoadGimmickObjectDataTable()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> TargetDataTable(TEXT("/Script/Engine.DataTable'/Game/PledgeOfStarlight/DataTable/DT_GimmickObjectDataTable.DT_GimmickObjectDataTable'"));
	if(TargetDataTable.Succeeded())
	{
		GimmickObjectDataTable = TargetDataTable.Object;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Gimmick Object Data Table Load Failed"));
	}
	return;
}
