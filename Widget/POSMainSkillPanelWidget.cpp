// Fill out your copyright notice in the Description page of Project Settings.


#include "POSMainSkillPanelWidget.h"

#include "POSSkillSingleSlotWidget.h"
#include "Components/HorizontalBox.h"
#include "PledgeOfStarlight/Interface/POSSkillSubSystemInterface.h"
#include "PledgeOfStarlight/Skill/POSSkillGameInstanceSubSystem.h"
#include "PledgeOfStarlight/Struct/POSSlotData.h"

void UPOSMainSkillPanelWidget::SetUpSkillUI()
{
	IPOSSkillSubSystemInterface* POSSkillSubSystemInterface = Cast<IPOSSkillSubSystemInterface>(GetGameInstance()->GetSubsystem<UPOSSkillGameInstanceSubSystem>());
	TMap<FName, FSkillMasterInfo> EarnedSkillData = POSSkillSubSystemInterface->GetEarnedSkillDataList();

	for (auto Data : EarnedSkillData)
	{
		//새로운 Horizontal Line 추가
		if(CurrentHorizontalSkillAmount == 0)
		{
			MenuSlotLineInstance = CreateWidget<UUserWidget>(GetOwningPlayer(), WBP_MenuSlot);
			SkillListSizeBox->AddChild(MenuSlotLineInstance);
		}

		//Horizontal Line에 요소 추가
		UPOSSkillSingleSlotWidget* SkillSingleSlotInstance = CreateWidget<UPOSSkillSingleSlotWidget>(GetOwningPlayer(), WBP_POSSkillSingleSlot);
		FProperty* Property = SkillSingleSlotInstance->GetClass()->FindPropertyByName(TEXT("SlotData"));
		if(!Property)
		{
			UE_LOG(LogTemp, Warning, TEXT("SingleSlot Value Name Error"));
		}
		Property->ContainerPtrToValuePtr<FSlotData>(SkillSingleSlotInstance);
		FSlotData* SlotData = Property->ContainerPtrToValuePtr<FSlotData>(SkillSingleSlotInstance);
		if(SlotData)
		{
			SlotData->SlotType = ESlotType::Skill;
			SlotData->SkillMasterInfo = Data.Value; //Editorble 데이터 SubSystem에서 할당.
			SlotData->ItemMasterInfo = FItemMasterInfo();	
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("SingleSlotData Error"));
		}
		
		UHorizontalBox* SlotHorizontalBox = Cast<UHorizontalBox>(MenuSlotLineInstance->GetWidgetFromName("SlotHorizontalBox"));
		SlotHorizontalBox->AddChild(SkillSingleSlotInstance);

		//Button Down Bind
		SkillSingleSlotInstance->OnButtonDown.AddDynamic(this, &UPOSMainSkillPanelWidget::SetInfoSKillSlotButtonDown);

		//Horizontal라인의 요소 갯수 갱신
		if(CurrentHorizontalSkillAmount >= MaxHorizontalSkillAmount - 1)
		{
			CurrentHorizontalSkillAmount = 0;
		}
		else
		{
			CurrentHorizontalSkillAmount++;
		}
	}
	
	return;
	
}
