// Copyright Epic Games, Inc. All Rights Reserved.

#include "POSAttackTask.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/Engine.h"

UPOSAttackTask::UPOSAttackTask()
{
	NodeName = TEXT("POS Attack Task");
}

EBTNodeResult::Type UPOSAttackTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
	
	if (DistanceToTarget > AttackRange)
	{
		return EBTNodeResult::Failed;
	}
	
	float CurrentTime = GetWorld()->GetTimeSeconds();
	if (CurrentTime - LastAttackTime < AttackCooldown)
	{
		return EBTNodeResult::Failed;
	}
	
	if (AttackAnimationMontage)
	{
		ACharacter* Character = Cast<ACharacter>(ControlledPawn);
		if (Character && Character->GetMesh())
		{
			Character->GetMesh()->AnimScriptInstance->Montage_Play(AttackAnimationMontage);
		}
	}
	
	LastAttackTime = CurrentTime;
	
	Blackboard->SetValueAsBool("CanAttack", false);
	
	FTimerHandle AttackCooldownTimer;
	GetWorld()->GetTimerManager().SetTimer(
		AttackCooldownTimer,
		[Blackboard]()
		{
			if (Blackboard)
			{
				Blackboard->SetValueAsBool("CanAttack", true);
			}
		},
		AttackCooldown,
		false
	);

	return EBTNodeResult::Succeeded;
}
