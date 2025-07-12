// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "POSQuestInfo.generated.h"

enum class EPOSQuestUniqueType : uint8;
enum class EQuestType : uint8;

USTRUCT(BlueprintType)
struct FPOSQuestInfo :public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = "POS|Quest", EditAnywhere, BlueprintReadWrite)
	FName QuestID; //RowName과 동일하게 설정
	
	UPROPERTY(Category = "POS|Quest", EditAnywhere, BlueprintReadWrite)
	FText Title;
	
	UPROPERTY(Category = "POS|Quest", EditAnywhere, BlueprintReadWrite)
	FText Description;
	
	UPROPERTY(Category = "POS|Quest", EditAnywhere, BlueprintReadWrite)
	EPOSQuestUniqueType QuestUniqueType;

	UPROPERTY(Category = "POS|Quest", EditAnywhere, BlueprintReadWrite)
	EQuestType QuestType;
	
	UPROPERTY(Category = "POS|Quest", EditAnywhere, BlueprintReadWrite)
	FDataTableRowHandle QuestDetailTableHandler;
	
};
