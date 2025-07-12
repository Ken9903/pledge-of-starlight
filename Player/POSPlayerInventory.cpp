// Fill out your copyright notice in the Description page of Project Settings.


#include "POSPlayerInventory.h"


UPOSPlayerInventory::UPOSPlayerInventory()
{
}

TArray<FItemMasterInfo> UPOSPlayerInventory::GetInventoryItemDataList()
{
	return InventoryItemDataList;
}

void UPOSPlayerInventory::SetInventoryItemDataList(TArray<FItemMasterInfo> InInventoryItemDataList)
{
	this->InventoryItemDataList = InInventoryItemDataList;
}
