// Fill out your copyright notice in the Description page of Project Settings.


#include "POSUtilitySkillBase.h"

#include "POSSkillGameInstanceSubSystem.h"
#include "PledgeOfStarlight/Interface/POSSkillSubSystemInterface.h"

void APOSUtilitySkillBase::BeginPlay()
{
	Super::BeginPlay();
	UPOSSkillGameInstanceSubSystem* SkillSubSystem = GetGameInstance()->GetSubsystem<UPOSSkillGameInstanceSubSystem>();
	if(SkillSubSystem)
	{
		IPOSSkillSubSystemInterface* SkillSubSystemInterface = Cast<IPOSSkillSubSystemInterface>(SkillSubSystem);
		if(SkillSubSystemInterface)
		{
			FString EnumName = UEnum::GetValueAsString(SkillID);
			UtilitySkillData = SkillSubSystemInterface->GetUtilitySkillDataFromTable(FName(EnumName.Replace(TEXT("ESkillID::"), TEXT(""))));
		}
	}
	return;
}
