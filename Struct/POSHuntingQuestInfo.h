// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "POSHuntingQuestInfo.generated.h"

USTRUCT(BlueprintType)
struct FPOSHuntingQuestInfo :public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = "POS|Quest", EditAnywhere, BlueprintReadWrite)
	TArray<FName> TargetID;

	UPROPERTY(Category = "POS|Quest", EditAnywhere, BlueprintReadWrite)
	TArray<int32> Amount;
	
};
