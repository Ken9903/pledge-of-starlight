// Fill out your copyright notice in the Description page of Project Settings.


#include "POSPlayerAbility.h"

#include "Blueprint/UserWidget.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "PledgeOfStarlight/Struct/POSItemData.h"
#include "PledgeOfStarlight/Struct/POSSkillData.h"

// Sets default values for this component's properties
UPOSPlayerAbility::UPOSPlayerAbility()
{
	PresetDataList.Init(FSlotData(), 10);
	SkillPresetClassList.Init(nullptr, 10);
	ItemPresetClassList.Init(nullptr, 10);
	SkillSpawnPool.Init(nullptr,10);
	ItemSpawnPool.Init(nullptr,10);
}
void UPOSPlayerAbility::UsePreset(int32 InputNumber)
{
	FSlotData SlotData = PresetDataList[InputNumber];
	switch (SlotData.SlotType)
	{
	case ESlotType::Default:
		break;
	case ESlotType::Skill:
		if(IsValid(SkillSpawnPool[InputNumber]))
		{
			SkillSpawnPool[InputNumber]->UseSkill();
		}
		else
		{
			TSubclassOf<APOSSkillBase> SkillClass = SkillPresetClassList[InputNumber];
			APOSSkillBase* SpawnedSkill = GetWorld()->SpawnActor<APOSSkillBase>(
				SkillClass,
				GetOwner()->GetActorTransform(),
				FActorSpawnParameters()
				);

			SkillSpawnPool[InputNumber] = SpawnedSkill;
			ACharacter* POSPlayer = Cast<ACharacter>(GetOwner());
			SpawnedSkill->AttachToComponent(POSPlayer->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), NAME_None);
			
			SpawnedSkill->UseSkill();
		}
		break;
	case ESlotType::Item:
		if(IsValid(ItemSpawnPool[InputNumber]))
		{
			ItemSpawnPool[InputNumber]->UseItem();
		}
		else
		{
			TSubclassOf<APOSItemBase> ItemClass = ItemPresetClassList[InputNumber];
			APOSItemBase* SpawnedItem= GetWorld()->SpawnActor<APOSItemBase>(
				ItemClass,
				GetOwner()->GetActorTransform(),
				FActorSpawnParameters()
				);

			ItemSpawnPool[InputNumber] = SpawnedItem;
			ACharacter* POSPlayer = Cast<ACharacter>(GetOwner());
			SpawnedItem->AttachToComponent(POSPlayer->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), NAME_None);

			SpawnedItem->UseItem();
		}
		break;
	case ESlotType::Preset:
		break;
	default:
		break;
		
	}
}

void UPOSPlayerAbility::SetSkillPreset(int32 Index, TSubclassOf<APOSSkillBase> SkillClass)
{
	SkillPresetClassList[Index] = SkillClass;
}

void UPOSPlayerAbility::SetItemPreset(int32 Index, TSubclassOf<APOSItemBase> ItemClass)
{
	ItemPresetClassList[Index] = ItemClass;
}

bool UPOSPlayerAbility::CheckSkillPresetSlotValid(int32 Number)
{
	return IsValid(SkillPresetClassList[Number]);
}

TArray<FSlotData> UPOSPlayerAbility::GetPresetDataList()
{
	return PresetDataList;
}

void UPOSPlayerAbility::SetPresetDataList(TArray<FSlotData> InPresetDataList)
{
	this->PresetDataList = InPresetDataList;
}

void UPOSPlayerAbility::SetPresetData(int32 Index, FSlotData SlotData)
{
	PresetDataList[Index] = SlotData;
}

void UPOSPlayerAbility::BeginPlay()
{
	Super::BeginPlay();
	WBP_POSMainWidget = TSoftClassPtr<UUserWidget>(FSoftObjectPath(TEXT("/Game/PledgeOfStarlight/Widget/Main/WBP_POSMain.WBP_POSMain_C"))).LoadSynchronous();
	CreateInGamePresetPanel();
}

void UPOSPlayerAbility::CreateInGamePresetPanel()
{
	WBP_POSMainWidgetInstance = CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), WBP_POSMainWidget);
	WBP_POSMainWidgetInstance->AddToViewport();
	InitSkillPreset();
}

void UPOSPlayerAbility::InitSkillPreset()
{
	for (int i = 0; i < PresetDataList.Num(); i++)
	{
		FDataTableRowHandle DataTableRowHandle;
		switch (PresetDataList[i].SlotType)
		{
		case ESlotType::Default:
			break;

		case ESlotType::Skill:
			DataTableRowHandle = PresetDataList[i].SkillMasterInfo.MainSkillDataTable;
			if(DataTableRowHandle.DataTable)
			{
				FSkillData* SkillData;
				SkillData = DataTableRowHandle.DataTable->FindRow<FSkillData>(DataTableRowHandle.RowName, TEXT(""));
				SkillPresetClassList[i] = SkillData->SkillClass;
			}
			break;

		case ESlotType::Item:
			DataTableRowHandle = PresetDataList[i].ItemMasterInfo.MainItemDataTable;
			if(DataTableRowHandle.DataTable)
			{
				FItemData* ItemData;
				ItemData = DataTableRowHandle.DataTable->FindRow<FItemData>(DataTableRowHandle.RowName, TEXT(""));
				ItemPresetClassList[i] = ItemData->ItemClass;
			}
			break;

		case ESlotType::Preset:
			break;

		default:
			break;
		}
	}
	
	InitSpawnPool();
	
	//Preset UI Set
	UPOSSlotPresetWidget* POSSlotPresetWidget = Cast<UPOSSlotPresetWidget>(WBP_POSMainWidgetInstance->GetWidgetFromName(TEXT("WBP_SlotPreset")));
	if(POSSlotPresetWidget)
	{
		POSSlotPresetWidget->SetPresetData(PresetDataList);
	}
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Skill Preset Init Completed"));
	}
	
}

void UPOSPlayerAbility::InitSpawnPool()
{
	SkillSpawnPool.Init(nullptr, 10);
	ItemSpawnPool.Init(nullptr,10);
}


