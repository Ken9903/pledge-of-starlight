// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "POSFindPatrolPosTask.generated.h"

/**
 * 
 */
UCLASS()
class PLEDGEOFSTARLIGHT_API UPOSFindPatrolPosTask : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UPOSFindPatrolPosTask();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
