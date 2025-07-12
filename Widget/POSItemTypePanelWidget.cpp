// Fill out your copyright notice in the Description page of Project Settings.


#include "POSItemTypePanelWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/HorizontalBox.h"
#include "Components/ScrollBox.h"
#include "Kismet/GameplayStatics.h"
#include "PledgeOfStarlight/Interface/POSPlayerInterface.h"
#include "PledgeOfStarlight/Player/POSPlayerInventory.h"
#include "PledgeOfStarlight/Struct/POSItemData.h"
#include "PledgeOfStarlight/Struct/POSItemMasterInfo.h"
#include "GameFramework/Character.h"
#include "PledgeOfStarlight/Struct/POSSlotData.h"


void UPOSItemTypePanelWidget::SetUpItemUI()
{
	IPOSPlayerInterface* POSPlayerInterface = Cast<IPOSPlayerInterface>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if(!POSPlayerInterface)
	{
		UE_LOG(LogTemp, Warning, TEXT("POSPlayerInterface nullptr"));
		return;
	}
	TArray<FItemMasterInfo> InventoryData = POSPlayerInterface->GetPlayerInventory()->GetInventoryItemDataList();

	for (auto Data : InventoryData)
	{
		if(!CheckSameItemTypePanel(Data))
		{
			continue;
		}
		//새로운 Horizontal Line 추가
		if(CurrentHorizontalItemAmount == 0)
		{
			MenuSlotLineInstance = CreateWidget<UUserWidget>(GetOwningPlayer(), WBP_MenuSlot);
			ItemListSizeBox->AddChild(MenuSlotLineInstance);
		}

		//Horizontal Line에 요소 추가
		UUserWidget* ItemSingleSlotInstance = CreateWidget<UUserWidget>(GetOwningPlayer(), WBP_POSItemSingleSlot);
		FProperty* Property = ItemSingleSlotInstance->GetClass()->FindPropertyByName(TEXT("SlotData"));
		if(!Property)
		{
			UE_LOG(LogTemp, Warning, TEXT("SingleSlot Value Name Error"));
		}
		FSlotData* SlotData = Property->ContainerPtrToValuePtr<FSlotData>(ItemSingleSlotInstance);
		if(SlotData)
		{
			SlotData->SlotType = ESlotType::Item;
			SlotData->SkillMasterInfo = FSkillMasterInfo();
			SlotData->ItemMasterInfo = Data;	
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("SingleSlotData Error"));
		}
		
		UHorizontalBox* SlotHorizontalBox = Cast<UHorizontalBox>(MenuSlotLineInstance->WidgetTree->FindWidget("SlotHorizontalBox"));
		SlotHorizontalBox->AddChild(ItemSingleSlotInstance);

		//Horizontal라인의 요소 갯수 갱신
		if(CurrentHorizontalItemAmount >= MaxHorizontalItemAmount - 1)
		{
			CurrentHorizontalItemAmount = 0;
		}
		else
		{
			CurrentHorizontalItemAmount++;
		}
	}
	
	return;
}

bool UPOSItemTypePanelWidget::CheckSameItemTypePanel(FItemMasterInfo ItemMasterInfo)
{
	if(IsValid(ItemMasterInfo.MainItemDataTable.DataTable))
	{
		FDataTableRowHandle DataTableRowHandle = ItemMasterInfo.MainItemDataTable;
		FItemData* ItemData = DataTableRowHandle.DataTable->FindRow<FItemData>(DataTableRowHandle.RowName,TEXT(""));
		if(ItemData)
		{
			return ItemPanelType == ItemData->ItemType;
		}
		return false;
	}
	return false;
}
