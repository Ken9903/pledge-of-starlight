// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "POSEditableSkillData.generated.h"


USTRUCT(BlueprintType)
struct FEditableSkillData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = "POS|Skill", EditAnywhere, BlueprintReadWrite)
	int32 Level;

	UPROPERTY(Category = "POS|Skill", EditAnywhere, BlueprintReadWrite)
	int32 LevelProgress;
};
