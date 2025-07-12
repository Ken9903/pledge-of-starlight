// Fill out your copyright notice in the Description page of Project Settings.


#include "POSItemBase.h"

#include "POSItemGameInstanceSubSystem.h"

// Sets default values
APOSItemBase::APOSItemBase()
{
}

void APOSItemBase::BeginPlay()
{
	Super::BeginPlay();
	UPOSItemGameInstanceSubsystem* ItemSubSystem = GetGameInstance()->GetSubsystem<UPOSItemGameInstanceSubsystem>();
	if(ItemSubSystem)
	{
		IPOSItemSubSystemInterface* ItemSubSystemInterface = Cast<IPOSItemSubSystemInterface>(ItemSubSystem);
		if(ItemSubSystemInterface)
		{
			FString EnumName = UEnum::GetValueAsString(ItemID);
			ItemData = ItemSubSystemInterface->GetItemDataFromTable(FName(EnumName.Replace(TEXT("EItemID::"), TEXT(""))));
		}
	}
	return;
}


void APOSItemBase::UseItem()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Use Default Item"));
	}
	return;
}


