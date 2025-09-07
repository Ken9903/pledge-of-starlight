// Fill out your copyright notFire in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "POSAttackSkillBase.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "POSAttackFireSlash.generated.h"

/**
 * 
 */
UCLASS()
class PLEDGEOFSTARLIGHT_API APOSAttackFireSlash : public APOSAttackSkillBase
{
	GENERATED_BODY()

	APOSAttackFireSlash();

private:
	UPROPERTY(Category = "POS|Collision", VisibleAnywhere)
	TObjectPtr<USphereComponent> AttackCollision;
	
	UPROPERTY(Category = "POS|Effect", VisibleAnywhere)
	TObjectPtr<UNiagaraComponent> FireSlashEffect;

	virtual void BeginPlay() override;
	
	void UseSkill() override;

	UFUNCTION(Category = "POS|Collision")
	void PlayCollision();
	
	UFUNCTION(Category = "POS|Collision")
	void OffCollision();

	UFUNCTION(Category = "POS|Collision")
	void OnAttackCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
