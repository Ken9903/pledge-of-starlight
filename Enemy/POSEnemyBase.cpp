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

APOSEnemyBase::APOSEnemyBase()
{
	HitPoint = CreateDefaultSubobject<USceneComponent>(TEXT("HitPoint"));
	HitPoint->SetupAttachment(GetMesh());
	
	DialogueTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("DialogueTrigger"));
	DialogueTrigger->SetupAttachment(GetMesh());
	DialogueTrigger->SetSphereRadius(150.0f);
	
	CurrentAIState = EEnemyAIState::Patrol;
}

void APOSEnemyBase::TakeDamage(float Damage, float SoundDelay)
{
	SetAIState(EEnemyAIState::Hit);
	
	PlayDirectionalHitAnimation();
	
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
	
	AIControllerRef = Cast<AAIController>(GetController());
	
	// 플레이어 컨트롤러 캐시
	CachedPlayerController = GetWorld()->GetFirstPlayerController();
}

void APOSEnemyBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	AIControllerRef = Cast<AAIController>(NewController);
	
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

void APOSEnemyBase::SetAIState(EEnemyAIState NewState)
{
	CurrentAIState = NewState;
	
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
	SetAIState(EEnemyAIState::Patrol);
}




