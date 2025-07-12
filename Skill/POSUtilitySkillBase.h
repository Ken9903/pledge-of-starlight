// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "POSSkillBase.h"
#include "PledgeOfStarlight/Struct/POSUtilitySkillData.h"
#include "POSUtilitySkillBase.generated.h"

/**
 * 
 */
UCLASS()
class PLEDGEOFSTARLIGHT_API APOSUtilitySkillBase : public APOSSkillBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(Category = "POS|SKill", VisibleAnywhere)
	FUtilitySkillData UtilitySkillData;
	
};
