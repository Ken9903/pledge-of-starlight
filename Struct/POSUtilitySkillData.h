// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "POSUtilitySkillData.generated.h"

USTRUCT(BlueprintType)
struct FUtilitySkillData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = "POS|Skill", EditAnywhere)
	float HPHealAmount;

	UPROPERTY(Category = "POS|Skill", EditAnywhere)
	float MPHealAmount;
	
	UPROPERTY(Category = "POS|Skill", EditAnywhere)
	float SpeedPlusAmount;

	UPROPERTY(Category = "POS|Skill", EditAnywhere)
	float AttackPlusAmount;

	UPROPERTY(Category = "POS|Skill", EditAnywhere)
	float DefendPlusAmount;
	
};