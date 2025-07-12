// Fill out your copyright notice in the Description page of Project Settings.


#include "POSItemGameInstanceSubsystem.h"

UPOSItemGameInstanceSubsystem::UPOSItemGameInstanceSubsystem()
{
	LoadItemDataTable();
	LoadConsumableItemDataTable();
}

FItemData UPOSItemGameInstanceSubsystem::GetItemDataFromTable(FName RowName)
{
	if(!ItemDataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemDataTable nullptr"));
		return FItemData();
	}

	FItemData* ItemData = ItemDataTable->FindRow<FItemData>(RowName, TEXT(""));

	if (ItemData)
	{
		return *ItemData;
	}

	UE_LOG(LogTemp, Warning, TEXT("ItemDatable can not find %s"), *RowName.ToString());
	return FItemData();
}

FConsumableItemData UPOSItemGameInstanceSubsystem::GetConsumableItemDataFromTable(FName RowName)
{
	if(!ConsumableItemDataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("Consumable ItemDataTable nullptr"));
		return FConsumableItemData();
	}

	FConsumableItemData* ConsumableItemData = ConsumableItemDataTable->FindRow<FConsumableItemData>(RowName, TEXT(""));

	if (ConsumableItemData)
	{
		return *ConsumableItemData;
	}

	UE_LOG(LogTemp, Warning, TEXT("Consumable ItemDatable can not find %s"), *RowName.ToString());
	return FConsumableItemData();
}

void UPOSItemGameInstanceSubsystem::LoadItemDataTable()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> TargetDataTable(TEXT("/Script/Engine.DataTable'/Game/PledgeOfStarlight/DataTable/DT_ItemDataTable.DT_ItemDataTable'"));
	if(TargetDataTable.Succeeded())
	{
		ItemDataTable = TargetDataTable.Object;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("ItemDataTable Load Failed"));
	}
	return;
}

void UPOSItemGameInstanceSubsystem::LoadConsumableItemDataTable()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> TargetDataTable(TEXT("/Script/Engine.DataTable'/Game/PledgeOfStarlight/DataTable/DT_ConsumableItemDataTable.DT_ConsumableItemDataTable'"));
	if(TargetDataTable.Succeeded())
	{
		ConsumableItemDataTable = TargetDataTable.Object;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Consumable ItemDataTable Load Failed"));
	}
	return;
}
