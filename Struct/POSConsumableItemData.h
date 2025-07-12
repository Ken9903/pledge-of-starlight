// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "POSConsumableItemData.generated.h"

USTRUCT(BlueprintType)
struct FConsumableItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = "POS|Item", EditAnywhere, BlueprintReadWrite)
	bool bUnique;

	UPROPERTY(Category = "POS|Item", EditAnywhere, BlueprintReadWrite)
	int32 HPHealAmount;

	UPROPERTY(Category = "POS|Item", EditAnywhere, BlueprintReadWrite)
	int32 MPHealAmount;
};
