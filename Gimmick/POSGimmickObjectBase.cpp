// Fill out your copyright notice in the Description page of Project Settings.


#include "POSGimmickObjectBase.h"

#include "POSGimmickGameInstanceSubSystem.h"

// Sets default values
APOSGimmickObjectBase::APOSGimmickObjectBase()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;
}

void APOSGimmickObjectBase::InteractSkill(FName SkillID)
{
	for (auto Element : GimmickObjectInfo.SkillGimmickDataList)
	{
		if(Element.SkillID == SkillID)
		{
			if(Element.isRepeatable || !GimmickExecutionMap[SkillID])
			{
				UE_LOG(LogTemp, Log, TEXT("Play Skill Gimmick : %s "), *SkillID.ToString())
				//TODO : 실행 부분.
				GimmickExecutionMap[SkillID] = true; //GimmickObject같은 경우 Interact시 바로 시행 판정.
				GimmickSuccessMap[SkillID] = true;
				break;
			}
		}
	}
}

void APOSGimmickObjectBase::BeginPlay()
{
	Super::BeginPlay();
	UPOSGimmickGameInstanceSubSystem* GimmickSubSystem = GetGameInstance()->GetSubsystem<UPOSGimmickGameInstanceSubSystem>();
	if(GimmickSubSystem)
	{
		GimmickObjectInfo = GimmickSubSystem->GetGimmickObjectData(GimmickObjectID);
	}
	InitGimmickMap();
	return;
}

void APOSGimmickObjectBase::InitGimmickMap()
{
	if(isSaved)
	{
		return;
	}
	for (auto SkillGimmickData : GimmickObjectInfo.SkillGimmickDataList)
	{
		GimmickSuccessMap.Add(SkillGimmickData.SkillID, false);
		GimmickExecutionMap.Add(SkillGimmickData.SkillID, false);
	}
	isSaved = true;
	//TODO : Save
}
