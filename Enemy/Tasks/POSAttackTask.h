// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "POSAttackTask.generated.h"

UCLASS()
class PLEDGEOFSTARLIGHT_API UPOSAttackTask : public UBTTask_BlueprintBase
{
	GENERATED_BODY()
	
public:
	UPOSAttackTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(Category = "POS|Attack", EditAnywhere)
	float AttackRange = 150.0f;
	
	UPROPERTY(Category = "POS|Attack", EditAnywhere)
	UAnimMontage* AttackAnimationMontage;
	
	UPROPERTY(Category = "POS|Attack", EditAnywhere)
	float AttackCooldown = 2.0f;

private:
	float LastAttackTime = 0.0f;
};

