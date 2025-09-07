// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "POSEnemyAIController.generated.h"

UCLASS()
class PLEDGEOFSTARLIGHT_API APOSEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	APOSEnemyAIController();

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	// Blackboard 컴포넌트 접근자
	UBlackboardComponent* GetBlackboardComponent() const { return BlackboardComponent; }
	
	// BehaviorTree 컴포넌트 접근자
	UBehaviorTreeComponent* GetBehaviorTreeComponent() const { return BehaviorTreeComponent; }

protected:
	// AI 컴포넌트들
	UPROPERTY(Category = "POS|AI", VisibleAnywhere)
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
	
	UPROPERTY(Category = "POS|AI", VisibleAnywhere)
	TObjectPtr<UBlackboardComponent> BlackboardComponent;
public:
	// Blackboard 키들
	static const FName AIStateKey;
	static const FName TargetActorKey;
	static const FName HomeLocationKey;
	static const FName PatrolLocationKey;
	static const FName IsPlayerDetectedKey;
	static const FName CanAttackKey;
};



