// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "POSSkillGimmickData.h"
#include "POSGimmickObjectInfo.generated.h"


USTRUCT(BlueprintType)
struct FPOSGimmickObjectInfo :public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = "POS|Gimmick", EditAnywhere, BlueprintReadWrite)
	TArray<FPOSSkillGimmickData> SkillGimmickDataList;
	
};
