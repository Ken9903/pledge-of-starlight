// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PledgeOfStarlight/Struct/POSConsumableItemData.h"
#include "PledgeOfStarlight/Struct/POSItemData.h"
#include "UObject/Interface.h"
#include "POSItemSubSystemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPOSItemSubSystemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PLEDGEOFSTARLIGHT_API IPOSItemSubSystemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual FItemData GetItemDataFromTable(FName RowName) = 0;
	virtual FConsumableItemData GetConsumableItemDataFromTable(FName RowName) = 0;
};
