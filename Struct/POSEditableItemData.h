// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "POSEditableItemData.Generated.h"

USTRUCT(BlueprintType)
struct FEditableItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = "POS|Item", EditAnywhere, BlueprintReadWrite)
	int32 Amount;
};

