// Fill out your copyright notice in the Description page of Project Settings.


#include "POSSkillBase.h"

#include "POSSkillGameInstanceSubSystem.h"
#include "Kismet/GameplayStatics.h"
#include "PledgeOfStarlight/PledgeOfStarlightCharacter.h"

APOSSkillBase::APOSSkillBase()
{
	static ConstructorHelpers::FObjectFinder<USoundWave> SoundAsset(TEXT("/Script/Engine.SoundWave'/Game/Free_Sounds_Pack/Cash_Register_1-2.Cash_Register_1-2'"));
	if (SoundAsset.Succeeded())
	{
		UsingSound = SoundAsset.Object;
	}
}

void APOSSkillBase::BeginPlay()
{
	Super::BeginPlay();
	UPOSSkillGameInstanceSubSystem* SkillSubSystem = GetGameInstance()->GetSubsystem<UPOSSkillGameInstanceSubSystem>();
	if(SkillSubSystem)
	{
		IPOSSkillSubSystemInterface* SkillSubSystemInterface = Cast<IPOSSkillSubSystemInterface>(SkillSubSystem);
		if(SkillSubSystemInterface)
		{
			FString EnumName = UEnum::GetValueAsString(SkillID);
			SkillData = SkillSubSystemInterface->GetSkillDataFromTable(FName(EnumName.Replace(TEXT("ESkillID::"), TEXT(""))));
		}
	}
	return;
}

void APOSSkillBase::UseSkill()
{
	// 스킬 기믹 발동, 정보 전달.
	SendSkillIDToInteractGimmick();
}

void APOSSkillBase::InitTransform()
{
	SetActorRelativeLocation(AttachPosition);
	SetActorRelativeRotation(AttachRotation);
	return;
}

void APOSSkillBase::SendSkillIDToInteractGimmick()
{
	for (auto Element : Cast<APledgeOfStarlightCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->GimmickInteractObjectList)
	{
		FString EnumName = UEnum::GetValueAsString(SkillID);
		Element->InteractSkill(FName(EnumName.Replace(TEXT("ESkillID::"), TEXT(""))));
	}
}
