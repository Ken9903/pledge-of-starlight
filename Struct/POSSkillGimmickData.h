// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "POSSkillGimmickData.generated.h"

USTRUCT(BlueprintType)
struct FPOSSkillGimmickData :public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = "POS|Gimmick", EditAnywhere, BlueprintReadWrite)
	FName SkillID;

	UPROPERTY(Category = "POS|Gimmick", EditAnywhere, BlueprintReadWrite)
	bool isRepeatable;
	
};
