// Fill out your copyright notice in the Description page of Project Settings.


#include "POSEnemyBase.h"

#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APOSEnemyBase::APOSEnemyBase()
{
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	RootComponent = SkeletalMesh;
	
	HitPoint = CreateDefaultSubobject<USceneComponent>(TEXT("HitPoint"));
	HitPoint->SetupAttachment(SkeletalMesh);
	
	DialogueTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("DialogueTrigger"));
	DialogueTrigger->SetupAttachment(SkeletalMesh);
	DialogueTrigger->SetSphereRadius(150.0f);

}

void APOSEnemyBase::TakeDamage(float Damage, float SoundDelay)
{
	if(SoundDelay == 0) //Timer Delay가 0이면 실행이 인됨.
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
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Take Damage : %.2f"), Damage));
	}
	return;
}

USceneComponent* APOSEnemyBase::GetHitPoint()
{
	return HitPoint;
}

void APOSEnemyBase::PlayHitSound()
{
	if (HitSound)
	{
		UGameplayStatics::PlaySound2D(this, HitSound);
	}
}




