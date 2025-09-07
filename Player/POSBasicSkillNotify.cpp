// Copyright Epic Games, Inc. All Rights Reserved.

#include "POSBasicSkillNotify.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "PledgeOfStarlight/Player/POSPlayerAbility.h"

UPOSBasicSkillNotify::UPOSBasicSkillNotify()
{
	// 기본 설정
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

	// 1. 캐시된 참조가 유효한지 확인
	if (CachedPlayerAbility.IsValid() && CachedOwner.IsValid())
	{
		// 캐시된 참조가 유효하면 바로 사용
		CachedPlayerAbility->UsePreset(0);
		return;
	}

	// 2. 캐시가 무효하면 새로 찾기 (첫 번째 실행 또는 캐시 무효화)
	AActor* Owner = MeshComp->GetOwner();
	if (!Owner)
	{
		return;
	}

	// 3. Character로 캐스팅 (한 번만)
	ACharacter* Character = Cast<ACharacter>(Owner);
	if (!Character)
	{
		return;
	}

	// 4. PlayerAbility 찾기 (한 번만)
	UPOSPlayerAbility* PlayerAbility = Character->FindComponentByClass<UPOSPlayerAbility>();
	if (!PlayerAbility)
	{
		return;
	}

	// 5. 캐시 업데이트
	CachedPlayerAbility = PlayerAbility;
	CachedOwner = Owner;

	// 6. 0번 슬롯 UseSkill 호출
	PlayerAbility->UsePreset(0);
}
