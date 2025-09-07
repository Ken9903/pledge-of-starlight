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

// ========================================
// 생성자
// ========================================
APOSEnemyAIController::APOSEnemyAIController()
{
	// AI 컴포넌트들 생성
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

// ========================================
// AI 컨트롤러 생명주기 관리
// ========================================
void APOSEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// EnemyBase로 캐스팅
	APOSEnemyBase* Enemy = Cast<APOSEnemyBase>(InPawn);
	if (!Enemy)
	{
		return;
	}
	// BehaviorTree 실행
	UBehaviorTree* BT = Enemy->BehaviorTree;
	if (!BT)
	{
		return;
	}
	
	RunBehaviorTree(BT);
	
	// 로그 출력
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, 
			TEXT("Enemy AI Controller: BehaviorTree Started"));
	}
}

void APOSEnemyAIController::OnUnPossess()
{
	Super::OnUnPossess();

	// BehaviorTree 정지
	if (BehaviorTreeComponent)
	{
		BehaviorTreeComponent->StopTree();
	}
}
