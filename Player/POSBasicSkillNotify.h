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
	void UsePlayerAbilitySlot0(USkeletalMeshComponent* MeshComp);
	
	UPROPERTY()
	TWeakObjectPtr<UPOSPlayerAbility> CachedPlayerAbility;
	
	UPROPERTY()
	TWeakObjectPtr<AActor> CachedOwner;
};
