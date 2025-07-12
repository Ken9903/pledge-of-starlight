// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "POSEditableSkillData.h"
#include "POSSkillMasterInfo.generated.h"

USTRUCT(BlueprintType)
struct FSkillMasterInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = "POS|Skill", EditAnywhere, BlueprintReadWrite)
	FEditableSkillData EditableData;

	UPROPERTY(Category = "POS|Skill", EditAnywhere, BlueprintReadWrite)
	FDataTableRowHandle MainSkillDataTable;
	
	UPROPERTY(Category = "POS|Skill", EditAnywhere, BlueprintReadWrite)
	FDataTableRowHandle SubSkillDataTable;
	
};
