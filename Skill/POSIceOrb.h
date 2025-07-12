// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "POSAttackSkillBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "POSIceOrb.generated.h"

/**
 * 
 */
UCLASS()
class PLEDGEOFSTARLIGHT_API APOSIceOrb : public APOSAttackSkillBase
{
	GENERATED_BODY()
	
public:
	APOSIceOrb();

	UPROPERTY(Category = "POS|Physics", VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

private:
	UPROPERTY(Category = "POS|Effect", VisibleAnywhere)
	TObjectPtr<UNiagaraComponent> IceOrbNiagaraComponent;

	UPROPERTY(Category = "POS|Collision", VisibleAnywhere)
	TObjectPtr<USphereComponent> AttackCollision;

	UPROPERTY(Category = "POS|Physics", EditDefaultsOnly)
	float HomingAccelerationMagnitude = 3000;

	UPROPERTY(Category = "POS|Physics", VisibleAnywhere)
	FVector HomingVelocity = FVector(1, 400, 400);

	FTimerHandle StartTimerHandle;
	FTimerHandle DestroyTimerHandle;

	UPROPERTY(Category = "POS|Parameter", EditAnywhere)
	float ChasingDelay = 0.1f;
	
	UPROPERTY(Category = "POS|Parameter", EditAnywhere)
	float LifeTime = 2.0f;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(Category = "POS|Skill")
	void StartChasing();

	UFUNCTION(Category = "POS|Skill")
	void DestroyIceOrbActor();

	UFUNCTION(Category = "POS|Collision")
	void OnAttackCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
