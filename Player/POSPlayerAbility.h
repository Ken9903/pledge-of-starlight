// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PledgeOfStarlight/Skill/POSSkillBase.h"
#include "PledgeOfStarlight/Item/POSItemBase.h"
#include "PledgeOfStarlight/Struct/POSSlotData.h"
#include "PledgeOfStarlight/Widget/POSSlotPresetWidget.h"
#include "POSPlayerAbility.generated.h"

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLEDGEOFSTARLIGHT_API UPOSPlayerAbility : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPOSPlayerAbility();

	UFUNCTION(Category = "POS|Preset")
	void UsePreset(int32 InputNumber);

	UFUNCTION(Category = "POS|Preset", BlueprintCallable)
	void SetSkillPreset(int32 Index, TSubclassOf<APOSSkillBase> SkillClass);
	
	UFUNCTION(Category = "POS|Preset", BlueprintCallable)
	void SetItemPreset(int32 Index, TSubclassOf<APOSItemBase> ItemClass);

	UFUNCTION(Category = "POS|Preset", BlueprintCallable)
	void SetPresetData(int32 Index, FSlotData SlotData);

	UFUNCTION(Category = "POS|Preset")
	bool CheckSkillPresetSlotValid(int32 Number);

	UFUNCTION(Category = "POS|Preset", BlueprintCallable)
	TArray<FSlotData> GetPresetDataList();
	
	UPROPERTY(Category = "POS|Preset", VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UUserWidget> WBP_POSMainWidgetInstance;

	UFUNCTION(Category = "POS|Preset")
	void SetPresetDataList(TArray<FSlotData> InPresetDataList);

	UFUNCTION(Category = "POS|Preset", BlueprintCallable)
	void CreateInGamePresetPanel();

private:
	//MasterInfo를 가져오지만 클래스만 참조함. TODO : Editable같은 혼동을 일으키는 수치는 나중에 삭제 -> SubSystem에서 관리
	UPROPERTY(Category = "POS|Preset", EditAnywhere, meta = (ToolTip = "클래스만 참조. Editable같은 수치는 삭제 예정, 수치관련 정보는 SubSystem에서 관리"))
	TArray<FSlotData> PresetDataList;

	UPROPERTY(Category = "POS|Preset", VisibleAnywhere)
	TArray<TSubclassOf<APOSSkillBase>> SkillPresetClassList;

	UPROPERTY(Category = "POS|Preset", VisibleAnywhere)
	TArray<TSubclassOf<APOSItemBase>> ItemPresetClassList;

	UPROPERTY(Category = "POS|Preset", VisibleAnywhere)
	TArray<APOSSkillBase*> SkillSpawnPool;

	UPROPERTY(Category = "POS|Preset", VisibleAnywhere)
	TArray<APOSItemBase*> ItemSpawnPool;

	UPROPERTY(Category = "POS|Preset", EditDefaultsOnly)
	TSubclassOf<UUserWidget> WBP_POSMainWidget;

	/*UPROPERTY(Category = "POS|Preset", VisibleAnywhere)
	TObjectPtr<class APOSDefaultSkill> DefaultSkill;
	
	UPROPERTY(Category = "POS|Preset", VisibleAnywhere)
	TObjectPtr<class APOSDefaultItem> DefaultItem;*/

	virtual void BeginPlay() override;
	
	UFUNCTION(Category = "POS|Preset")
	void InitSkillPreset();

	UFUNCTION(Category = "POS|Preset", BlueprintCallable)
	void InitSpawnPool();
		
};
