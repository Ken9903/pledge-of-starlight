// Copyright Epic Games, Inc. All Rights Reserved.

#include "POSChaseTask.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UPOSChaseTask::UPOSChaseTask()
{
	NodeName = TEXT("POS Chase Task");
}

EBTNodeResult::Type UPOSChaseTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	APawn* ControlledPawn = AIController->GetPawn();
	if (!ControlledPawn)
	{
		return EBTNodeResult::Failed;
	}
	
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard)
	{
		return EBTNodeResult::Failed;
	}

	AActor* TargetActor = Cast<AActor>(Blackboard->GetValueAsObject("TargetActor"));
	if (!TargetActor)
	{
		return EBTNodeResult::Failed;
	}

	float DistanceToTarget = FVector::Dist(ControlledPawn->GetActorLocation(), TargetActor->GetActorLocation());
	
	if (DistanceToTarget > StopChaseDistance)
	{
		Blackboard->SetValueAsObject("TargetActor", nullptr);
		Blackboard->SetValueAsBool("IsPlayerDetected", false);
		return EBTNodeResult::Failed;
	}
	
	ACharacter* Character = Cast<ACharacter>(ControlledPawn);
	if (Character && Character->GetCharacterMovement())
	{
		Character->GetCharacterMovement()->MaxWalkSpeed = ChaseSpeed;
	}
	
	AIController->MoveToActor(TargetActor);

	return EBTNodeResult::Succeeded;
}
