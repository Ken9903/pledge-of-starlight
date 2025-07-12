// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PledgeOfStarlight/Struct/POSGimmickObjectInfo.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "POSGimmickGameInstanceSubSystem.generated.h"

/**
 * 
 */
UCLASS()
class PLEDGEOFSTARLIGHT_API UPOSGimmickGameInstanceSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UPOSGimmickGameInstanceSubSystem();

	UFUNCTION(Category = "POS|Gimmick", BlueprintCallable)
	FPOSGimmickObjectInfo GetGimmickObjectData(FName GimmickObjectID);

private:
	UPROPERTY(Category = "POS|Gimmick", VisibleDefaultsOnly)
	TObjectPtr<UDataTable> GimmickObjectDataTable;

	UFUNCTION(Category = "POS|Gimmick")
	void LoadGimmickObjectDataTable();
	
};
