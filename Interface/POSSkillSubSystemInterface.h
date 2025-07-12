// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PledgeOfStarlight/Struct/POSSkillData.h"
#include "UObject/Interface.h"
#include "POSSkillSubSystemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPOSSkillSubSystemInterface : public UInterface
{
	GENERATED_BODY()
};

class PLEDGEOFSTARLIGHT_API IPOSSkillSubSystemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(Category = "POS|Skill")
	virtual FSkillData GetSkillDataFromTable(FName RowName) = 0;
	
	UFUNCTION(Category = "POS|Skill")
	virtual FUtilitySkillData GetUtilitySkillDataFromTable(FName RowName) = 0;

	UFUNCTION(Category = "POS|Skill")
	virtual TMap<FName, FSkillMasterInfo> GetEarnedSkillDataList() = 0;
};
