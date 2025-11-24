// Copyright Epic Games, Inc. All Rights Reserved.

#include "POSBasicSkillNotify.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "PledgeOfStarlight/Player/POSPlayerAbility.h"

UPOSBasicSkillNotify::UPOSBasicSkillNotify()
{
}

void UPOSBasicSkillNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		UsePlayerAbilitySlot0(MeshComp);
	}
}

void UPOSBasicSkillNotify::UsePlayerAbilitySlot0(USkeletalMeshComponent* MeshComp)
{
	if (!MeshComp)
	{
		return;
	}
	
	if (CachedPlayerAbility.IsValid() && CachedOwner.IsValid())
	{
		CachedPlayerAbility->UsePreset(0);
		return;
	}

	AActor* Owner = MeshComp->GetOwner();
	if (!Owner)
	{
		return;
	}

	ACharacter* Character = Cast<ACharacter>(Owner);
	if (!Character)
	{
		return;
	}

	UPOSPlayerAbility* PlayerAbility = Character->FindComponentByClass<UPOSPlayerAbility>();
	if (!PlayerAbility)
	{
		return;
	}

	CachedPlayerAbility = PlayerAbility;
	CachedOwner = Owner;

	PlayerAbility->UsePreset(0);
}
