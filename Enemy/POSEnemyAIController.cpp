// Copyright Epic Games, Inc. All Rights Reserved.

#include "POSEnemyAIController.h"
#include "PledgeOfStarlight/Enemy/POSEnemyBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "Engine/Engine.h"

const FName APOSEnemyAIController::HomeLocationKey(TEXT("HomeLocation"));
const FName APOSEnemyAIController::AIStateKey(TEXT("AIState"));
const FName APOSEnemyAIController::TargetActorKey(TEXT("TargetActor"));
const FName APOSEnemyAIController::PatrolLocationKey(TEXT("PatrolLocation"));
const FName APOSEnemyAIController::IsPlayerDetectedKey(TEXT("IsPlayerDetected"));
const FName APOSEnemyAIController::CanAttackKey(TEXT("CanAttack"));

APOSEnemyAIController::APOSEnemyAIController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

void APOSEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	APOSEnemyBase* Enemy = Cast<APOSEnemyBase>(InPawn);
	if (!Enemy)
	{
		return;
	}
	UBehaviorTree* BT = Enemy->BehaviorTree;
	if (!BT)
	{
		return;
	}
	
	RunBehaviorTree(BT);
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, 
			TEXT("Enemy AI Controller: BehaviorTree Started"));
	}
}

void APOSEnemyAIController::OnUnPossess()
{
	Super::OnUnPossess();

	if (BehaviorTreeComponent)
	{
		BehaviorTreeComponent->StopTree();
	}
}
