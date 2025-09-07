// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "POSBasicSkillNotify.generated.h"

class UPOSPlayerAbility;

UCLASS(Blueprintable, BlueprintType)
class PLEDGEOFSTARLIGHT_API UPOSBasicSkillNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	UPOSBasicSkillNotify();

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

private:
	// PlayerAbility의 0번 슬롯 UseSkill 호출 (최적화 버전)
	void UsePlayerAbilitySlot0(USkeletalMeshComponent* MeshComp);
	
	// 캐싱된 PlayerAbility 참조 (성능 최적화)
	UPROPERTY()
	TWeakObjectPtr<UPOSPlayerAbility> CachedPlayerAbility;
	
	// 캐시된 Owner 참조
	UPROPERTY()
	TWeakObjectPtr<AActor> CachedOwner;
};
