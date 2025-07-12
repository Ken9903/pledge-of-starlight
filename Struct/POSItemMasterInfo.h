// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "POSEditableItemData.h"
#include "POSItemMasterInfo.generated.h"

USTRUCT(BlueprintType)
struct FItemMasterInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = "POS|Item", EditAnywhere, BlueprintReadWrite)
	FEditableItemData EditableData;

	UPROPERTY(Category = "POS|Item", EditAnywhere, BlueprintReadWrite)
	FDataTableRowHandle MainItemDataTable;
	
	UPROPERTY(Category = "POS|Item", EditAnywhere, BlueprintReadWrite)
	FDataTableRowHandle SubItemDataTable;
	
};
