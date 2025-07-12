// Fill out your copyright notice in the Description page of Project Settings.


#include "POSSkillSingleSlotWidget.h"

void UPOSSkillSingleSlotWidget::TriggerButtonDownEvent(FSkillMasterInfo SkillMasterInfo)
{
	OnButtonDown.Broadcast(SkillMasterInfo);
}
