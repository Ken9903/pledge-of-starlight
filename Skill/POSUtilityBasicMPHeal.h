// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "POSUtilitySkillBase.h"
#include "POSUtilityBasicMPHeal.generated.h"

/**
 * 
 */
UCLASS()
class PLEDGEOFSTARLIGHT_API APOSUtilityBasicMPHeal : public APOSUtilitySkillBase
{
	GENERATED_BODY()

public:
	APOSUtilityBasicMPHeal();
	
private:
	UPROPERTY(Category = "POS|Effect", EditDefaultsOnly)
	TObjectPtr<UNiagaraComponent> MPHealNiagaraComponent;
	
	virtual void BeginPlay() override;

	virtual void UseSkill() override;
};
