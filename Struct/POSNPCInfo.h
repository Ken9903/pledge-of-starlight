// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "POSSkillGimmickData.h"
#include "POSNPCInfo.generated.h"

enum class ENPCType : uint8;
struct FPOSQuestInfo;

USTRUCT(BlueprintType)
struct FPOSNPCInfo :public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = "POS|NPC", EditAnywhere, BlueprintReadWrite)
	FName NPCName;

	UPROPERTY(Category = "POS|NPC", EditAnywhere, BlueprintReadWrite)
	ENPCType NPCType;

	UPROPERTY(Category = "POS|Quest", EditAnywhere, BlueprintReadWrite)
	TArray<FName> QuestIDList;

	UPROPERTY(Category = "POS|Gimmick", EditAnywhere, BlueprintReadWrite)
	TArray<FPOSSkillGimmickData> SkillGimmickDataList;
};
