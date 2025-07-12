// Fill out your copyright notice in the Description page of Project Settings.


#include "POSConsumableItem.h"
#include "POSItemGameInstanceSubsystem.h"

void APOSConsumableItem::BeginPlay()
{
	Super::BeginPlay();
	UPOSItemGameInstanceSubsystem* ItemSubSystem = GetGameInstance()->GetSubsystem<UPOSItemGameInstanceSubsystem>();
	if(ItemSubSystem)
	{
		IPOSItemSubSystemInterface* ItemSubSystemInterface = Cast<IPOSItemSubSystemInterface>(ItemSubSystem);
		if(ItemSubSystemInterface)
		{
			FString EnumName = UEnum::GetValueAsString(ItemID);
			ConsumableItemData = ItemSubSystemInterface->GetConsumableItemDataFromTable(FName(EnumName.Replace(TEXT("EItemID::"), TEXT(""))));
		}
	}
	return;
}