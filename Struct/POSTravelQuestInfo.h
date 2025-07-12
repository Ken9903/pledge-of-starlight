// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "POSTravelQuestInfo.generated.h"

USTRUCT(BlueprintType)
struct FPOSTravelQuestInfo :public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = "POS|Quest", EditAnywhere, BlueprintReadWrite)
	FName TargetID;
};
