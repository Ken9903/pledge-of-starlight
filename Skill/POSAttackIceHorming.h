// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "POSAttackSkillBase.h"
#include "POSIceOrb.h"
#include "Components/SphereComponent.h"
#include "POSAttackIceHorming.generated.h"

/**
 * 
 */
UCLASS()
class PLEDGEOFSTARLIGHT_API APOSAttackIceHorming : public APOSAttackSkillBase
{
	GENERATED_BODY()
public:
	APOSAttackIceHorming();

private:
	UPROPERTY(Category = "POS|Root", VisibleAnywhere)
	TObjectPtr<USceneComponent> RootSceneComponent;
	
	UPROPERTY(Category = "POS|Collision", VisibleAnywhere)
	TObjectPtr<USphereComponent> HitSearchArea;

	UPROPERTY(Category = "POS|Skill", EditDefaultsOnly)
	TSubclassOf<APOSIceOrb> POSIceOrbClass;
	
	UPROPERTY(Category = "POS|Skill", VisibleAnywhere)
	TObjectPtr<APOSIceOrb> POSIceOrb;

	virtual void BeginPlay() override;

	virtual void UseSkill() override;

	UFUNCTION(Category = "POS|Collsion")
	void StartCollisionTrigger();
	
	UFUNCTION(Category = "POS|Collsion")
	void EndCollisionTrigger();

	UFUNCTION(Category = "POS|Collision")
	void OnHitSearchCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
