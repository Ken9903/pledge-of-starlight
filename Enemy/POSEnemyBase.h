// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "PledgeOfStarlight/Interface/POSEnemyInterface.h"
#include "PledgeOfStarlight/Enum/POSEnemyAIState.h"
#include "POSEnemyBase.generated.h"

UCLASS()
class PLEDGEOFSTARLIGHT_API APOSEnemyBase : public ACharacter, public IPOSEnemyInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APOSEnemyBase();

	virtual void TakeDamage(float Damage, float SoundDelay) override;

	virtual USceneComponent* GetHitPoint() override;

	// AI 관련 함수들
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;

	// 피격 애니메이션 재생
	UFUNCTION(Category = "POS|Animation")
	void PlayHitAnimation();

	// 방향별 피격 애니메이션 재생
	UFUNCTION(Category = "POS|Animation")
	void PlayDirectionalHitAnimation();

	// 피격 상태에서 복구
	UFUNCTION(Category = "POS|AI")
	void RecoverFromHit();

	// AI 상태 관리
	UFUNCTION(Category = "POS|AI")
	void SetAIState(EEnemyAIState NewState);

	UFUNCTION(Category = "POS|AI")
	EEnemyAIState GetAIState() const { return CurrentAIState; }

	// AI 컨트롤러 접근자
	UFUNCTION(Category = "POS|AI")
	AAIController* GetAIController() const { return AIControllerRef; }

public:
	// AI 관련 컴포넌트들
	UPROPERTY(Category = "POS|AI", EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UBehaviorTree> BehaviorTree;

protected:
	// AI 관련 컴포넌트들
	UPROPERTY(Category = "POS|AI", EditAnywhere)
	TObjectPtr<UBlackboardData> BlackboardData;

	// 애니메이션 몽타주들
	UPROPERTY(Category = "POS|Animation", EditAnywhere)
	TObjectPtr<UAnimMontage> HitAnimationMontage;

	// 4방향 히트 몽타주들
	UPROPERTY(Category = "POS|Animation", EditAnywhere)
	TObjectPtr<UAnimMontage> HitAnimationMontage_Front;

	UPROPERTY(Category = "POS|Animation", EditAnywhere)
	TObjectPtr<UAnimMontage> HitAnimationMontage_Back;

	UPROPERTY(Category = "POS|Animation", EditAnywhere)
	TObjectPtr<UAnimMontage> HitAnimationMontage_Left;

	UPROPERTY(Category = "POS|Animation", EditAnywhere)
	TObjectPtr<UAnimMontage> HitAnimationMontage_Right;

	UPROPERTY(Category = "POS|Animation", EditAnywhere)
	TObjectPtr<UAnimMontage> AttackAnimationMontage;

	// AI 설정값들
	UPROPERTY(Category = "POS|AI_Settings", EditAnywhere)
	float PatrolRadius = 500.0f;

	UPROPERTY(Category = "POS|AI_Settings", EditAnywhere)
	float DetectionRadius = 300.0f;

	UPROPERTY(Category = "POS|AI_Settings", EditAnywhere)
	float AttackRange = 150.0f;

private:
	UPROPERTY(Category = "POS|AI", VisibleAnywhere)
	EEnemyAIState CurrentAIState = EEnemyAIState::Patrol;

	UPROPERTY(Category = "POS|AI", VisibleAnywhere)
	TObjectPtr<AAIController> AIControllerRef;

	// 캐시된 플레이어 컨트롤러
	UPROPERTY(Category = "POS|Player", VisibleAnywhere)
	TWeakObjectPtr<APlayerController> CachedPlayerController;

private:
	UPROPERTY(Category = "POS|Hit", VisibleAnywhere)
	TObjectPtr<USceneComponent> HitPoint;

	UPROPERTY(Category = "POS|Collision", VisibleAnywhere)
	TObjectPtr<USphereComponent> DialogueTrigger;
	
	UPROPERTY(Category = "POS|Sound", EditAnywhere)
	TObjectPtr<USoundBase> HitSound;

	UFUNCTION(Category = "POS|Sound")
	void PlayHitSound();

};
