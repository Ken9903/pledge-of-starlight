// Fill out your copyright notice in the Description page of Project Settings.


#include "POSEnemyBase.h"

#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"

// ========================================
// 생성자
// ========================================
APOSEnemyBase::APOSEnemyBase()
{
	// 기본 컴포넌트들 생성
	HitPoint = CreateDefaultSubobject<USceneComponent>(TEXT("HitPoint"));
	HitPoint->SetupAttachment(GetMesh());
	
	DialogueTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("DialogueTrigger"));
	DialogueTrigger->SetupAttachment(GetMesh());
	DialogueTrigger->SetSphereRadius(150.0f);
	
	// AI 상태 초기화
	CurrentAIState = EEnemyAIState::Patrol;
}

// ========================================
// 데미지 처리
// ========================================
void APOSEnemyBase::TakeDamage(float Damage, float SoundDelay)
{
	// 피격 상태로 변경
	SetAIState(EEnemyAIState::Hit);
	
	// 플레이어와의 상대적 방향에 따른 피격 애니메이션 재생
	PlayDirectionalHitAnimation();
	
	// 피격 사운드 재생 (지연 시간 적용)
	if (SoundDelay == 0.0f)
	{
		PlayHitSound();
	}
	else
	{
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(
			TimerHandle, 
			this,        
			&APOSEnemyBase::PlayHitSound, 
			SoundDelay,       
			false);
	}
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, 
		FString::Printf(TEXT("Enemy Take Damage: %.2f"), Damage));
	}
	
	FTimerHandle HitRecoveryTimer;
	GetWorldTimerManager().SetTimer(
		HitRecoveryTimer,
		this,
		&APOSEnemyBase::RecoverFromHit,
		1.0f, // 1초 후 복구
		false);
}

USceneComponent* APOSEnemyBase::GetHitPoint()
{
	return HitPoint;
}

void APOSEnemyBase::PlayHitSound()
{
	if (!HitSound)
	{
		return;
	}
	
	UGameplayStatics::PlaySound2D(this, HitSound);
}

void APOSEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
	// AI 컨트롤러 참조 저장
	AIControllerRef = Cast<AAIController>(GetController());
	
	// 플레이어 컨트롤러 캐시
	CachedPlayerController = GetWorld()->GetFirstPlayerController();
}

void APOSEnemyBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	AIControllerRef = Cast<AAIController>(NewController);
	
	// AI 컨트롤러가 BehaviorTree를 실행하도록 설정
	if (AIControllerRef && BehaviorTree)
	{
		AIControllerRef->RunBehaviorTree(BehaviorTree);
	}
}

void APOSEnemyBase::UnPossessed()
{
	Super::UnPossessed();
	
	AIControllerRef = nullptr;
}

void APOSEnemyBase::PlayHitAnimation()
{
	if (!HitAnimationMontage || !GetMesh())
	{
		return;
	}
	
	GetMesh()->AnimScriptInstance->Montage_Play(HitAnimationMontage);
}

void APOSEnemyBase::PlayDirectionalHitAnimation()
{
	if (!GetMesh())
	{
		return;
	}
	
	APlayerController* PlayerController = CachedPlayerController.Get();
	if (!PlayerController)
	{
		PlayerController = GetWorld()->GetFirstPlayerController();
		if (!PlayerController)
		{
			PlayHitAnimation();
			return;
		}
		CachedPlayerController = PlayerController;
	}

	ACharacter* PlayerCharacter = PlayerController->GetCharacter();
	if (!PlayerCharacter)
	{
		PlayHitAnimation();
		return;
	}

	//방향 계산
	FVector EnemyLocation = GetActorLocation();
	FVector PlayerLocation = PlayerCharacter->GetActorLocation();
	FVector DirectionToPlayer = (PlayerLocation - EnemyLocation).GetSafeNormal();
	
	FVector EnemyForward = GetActorForwardVector();
	FVector EnemyRight = GetActorRightVector();

	float ForwardDot = FVector::DotProduct(DirectionToPlayer, EnemyForward);
	float RightDot = FVector::DotProduct(DirectionToPlayer, EnemyRight);

	UAnimMontage* SelectedMontage = nullptr;
	if (ForwardDot > 0.707f) // 전방
	{
		SelectedMontage = HitAnimationMontage_Front;
	}
	else if (ForwardDot < -0.707f) // 후방
	{
		SelectedMontage = HitAnimationMontage_Back;
	}
	else if (RightDot > 0.707f) // 우측
	{
		SelectedMontage = HitAnimationMontage_Right;
	}
	else if (RightDot < -0.707f)// 좌측
	{
		SelectedMontage = HitAnimationMontage_Left;
	}

	// 선택된 몽타주가 없으면 기본 몽타주 사용
	if (!SelectedMontage)
	{
		SelectedMontage = HitAnimationMontage;
	}

	// 애니메이션 재생
	if (SelectedMontage)
	{
		GetMesh()->AnimScriptInstance->Montage_Play(SelectedMontage);
	}
}

// ========================================
// AI 상태 관리
// ========================================
void APOSEnemyBase::SetAIState(EEnemyAIState NewState)
{
	CurrentAIState = NewState;
	
	// AI 컨트롤러의 Blackboard에 상태 업데이트
	if (AIControllerRef)
	{
		UBlackboardComponent* Blackboard = AIControllerRef->GetBlackboardComponent();
		if (Blackboard)
		{
			Blackboard->SetValueAsEnum("AIState", static_cast<uint8>(NewState));
		}
	}
}

void APOSEnemyBase::RecoverFromHit()
{
	// 피격 상태에서 복구하여 패트롤 상태로 변경
	SetAIState(EEnemyAIState::Patrol);
}




