// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "POSSkillBase.h"
#include "NiagaraFunctionLibrary.h"
#include "POSAttackSkillBase.generated.h"

UCLASS()
class PLEDGEOFSTARLIGHT_API APOSAttackSkillBase : public APOSSkillBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Category = "POS|Hit", EditDefaultsOnly)
	UNiagaraSystem* HitFlash;

protected:
	UPROPERTY(Category = "POS|Hit", EditDefaultsOnly)
	float HitPreDelay = 0.0f;

	UPROPERTY(Category = "POS|Collision", EditDefaultsOnly)
	float CollisionDuration = 0.2f;

	UFUNCTION(Category = "POS|Hit")
	void HitEvent(AActor* HitActor, float Damage, float Delay, FVector HitLocation);

	UFUNCTION(Category = "POS|Hit")
	void AppearHitFlash(FVector HitLocation);
	
};
