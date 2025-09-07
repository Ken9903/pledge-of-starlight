// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "POSChaseTask.generated.h"

UCLASS()
class PLEDGEOFSTARLIGHT_API UPOSChaseTask : public UBTTask_BlueprintBase
{
	GENERATED_BODY()
	
public:
	UPOSChaseTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(Category = "POS|Chase", EditAnywhere)
	float ChaseSpeed = 600.0f;
	
	UPROPERTY(Category = "POS|Chase", EditAnywhere)
	float StopChaseDistance = 800.0f;
};

