// Fill out your copyright notice in the Description page of Project Settings.


#include "POSSkillBase.h"

#include "POSSkillGameInstanceSubSystem.h"
#include "Kismet/GameplayStatics.h"
#include "PledgeOfStarlight/PledgeOfStarlightCharacter.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"

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
	
	CachedPlayerCharacter = Cast<APledgeOfStarlightCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
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
	if (CachedPlayerCharacter.IsValid() && CachedPlayerCharacter->GetMesh() && SkillMontage)
	{
		UAnimInstance* AnimInstance = CachedPlayerCharacter->GetMesh()->GetAnimInstance();
		if (AnimInstance)
		{
			AnimInstance->Montage_Play(SkillMontage);
		}
	}
	
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
	if (CachedPlayerCharacter.IsValid())
	{
		for (auto Element : CachedPlayerCharacter->GimmickInteractObjectList)
		{
			FString EnumName = UEnum::GetValueAsString(SkillID);
			Element->InteractSkill(FName(EnumName.Replace(TEXT("ESkillID::"), TEXT(""))));
		}
	}
}
