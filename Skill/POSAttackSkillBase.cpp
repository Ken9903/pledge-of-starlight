// Fill out your copyright notice in the Description page of Project Settings.


#include "POSAttackSkillBase.h"
#include "TimerManager.h"
#include "PledgeOfStarlight/Interface/POSEnemyInterface.h"

void APOSAttackSkillBase::HitEvent(AActor* HitActor, float Damage, float Delay, FVector HitLocation)
{
	IPOSEnemyInterface* EnemyInterface = Cast<IPOSEnemyInterface>(HitActor);
	if(EnemyInterface)
	{
		EnemyInterface->TakeDamage(Damage, HitPreDelay);

		if(HitPreDelay == 0) // 타이머 길이가 0이면 실행이 안됨.
		{
			AppearHitFlash(HitLocation);
		}
		else
		{
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(
				TimerHandle,
				FTimerDelegate::CreateUObject(this, &APOSAttackSkillBase::AppearHitFlash, HitLocation),
				HitPreDelay,
				false
				);	
		}
	}
	return;
}

void APOSAttackSkillBase::AppearHitFlash(FVector HitLocation)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
	GetWorld(),     
	 HitFlash,  
	 HitLocation,       
	 FRotator(0,0,0),       
	 FVector(1,1,1),          
	 true,           
	 true,           
	 ENCPoolMethod::None, 
	 true
	 );
	return;
}