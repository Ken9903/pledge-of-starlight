// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "POSUtilitySkillBase.h"
#include "POSUtilityBasicHPHeal.generated.h"

/**
 * 
 */
UCLASS()
class PLEDGEOFSTARLIGHT_API APOSUtilityBasicHPHeal : public APOSUtilitySkillBase
{
	GENERATED_BODY()
	
public:
	APOSUtilityBasicHPHeal();

private:
	UPROPERTY(Category = "POS|Effect", EditDefaultsOnly)
	TObjectPtr<UNiagaraComponent> HPHealNiagaraComponent;
	
	virtual void BeginPlay() override;

	virtual void UseSkill() override;
	
};
