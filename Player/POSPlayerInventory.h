// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PledgeOfStarlight/Struct/POSItemMasterInfo.h"
#include "POSPlayerInventory.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLEDGEOFSTARLIGHT_API UPOSPlayerInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPOSPlayerInventory();

	UFUNCTION(Category = "POS|Inventory")
	TArray<FItemMasterInfo> GetInventoryItemDataList();

	UFUNCTION(Category = "POS|Inventory")
	void SetInventoryItemDataList(TArray<FItemMasterInfo> InInventoryItemDataList);

private:
	UPROPERTY(Category = "POS|Inventory", EditAnywhere)
	TArray<FItemMasterInfo> InventoryItemDataList;
	
};

