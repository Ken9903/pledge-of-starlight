// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PledgeOfStarlight/Enum/POSItemID.h"
#include "PledgeOfStarlight/Enum/POSItemType.h"
#include "POSItemData.generated.h"

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = "POSItem", EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(Category = "POS|Item", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class APOSItemBase> ItemClass;

	UPROPERTY(Category = "POS|Item", EditAnywhere, BlueprintReadWrite)
	EItemID ItemID;

	UPROPERTY(Category = "POS|Item", EditAnywhere, BlueprintReadWrite)
	EItemType ItemType;

	UPROPERTY(Category = "POS|Item", EditAnywhere, BlueprintReadWrite, meta = (MultiLine = "true"))
	FText ItemDescription;

	UPROPERTY(Category = "POS|Item", EditAnywhere, BlueprintReadWrite)
	bool IsSellable;

	UPROPERTY(Category = "POS|Item", EditAnywhere, BlueprintReadWrite)
	int32 SellGold;

	UPROPERTY(Category = "POS|Item", EditAnywhere, BlueprintReadWrite)
	int32 MaxPossession;

	UPROPERTY(Category = "POS|Item", EditAnywhere, BlueprintReadWrite)
	UTexture2D* IconImage;

	UPROPERTY(Category = "POS|Item", EditAnywhere, BlueprintReadWrite)
	UStaticMesh* ItemMesh;

	UPROPERTY(Category = "POS|Item", EditAnywhere, BlueprintReadWrite)
	int32 Unique;
};