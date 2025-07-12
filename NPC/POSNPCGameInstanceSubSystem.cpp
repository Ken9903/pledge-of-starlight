// Fill out your copyright notice in the Description page of Project Settings.


#include "POSNPCGameInstanceSubSystem.h"

UPOSNPCGameInstanceSubSystem::UPOSNPCGameInstanceSubSystem()
{
	LoadNPCDataTable();
}

FPOSNPCInfo UPOSNPCGameInstanceSubSystem::GetNPCData(FName NPCID)
{
	if(!NPCDataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("NPC DataTable nullptr"));
		return FPOSNPCInfo();
	}
	
	FPOSNPCInfo* NPCInfo = NPCDataTable->FindRow<FPOSNPCInfo>(NPCID, TEXT(""));
	if(NPCInfo)
	{
		return *NPCInfo;
	}

	UE_LOG(LogTemp, Warning, TEXT("NPC Datable can not find %s"), *NPCID.ToString());
	return FPOSNPCInfo();
}

void UPOSNPCGameInstanceSubSystem::LoadNPCDataTable()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> TargetDataTable(TEXT("/Script/Engine.DataTable'/Game/PledgeOfStarlight/DataTable/DT_NPCDataTable.DT_NPCDataTable'"));
	if(TargetDataTable.Succeeded())
	{
		NPCDataTable = TargetDataTable.Object;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("NPC Data Table Load Failed"));
	}
	return;
}
