// Fill out your copyright notice in the Description page of Project Settings.


#include "POSUtilityBasicMPHeal.h"

#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"

APOSUtilityBasicMPHeal::APOSUtilityBasicMPHeal()
{
	MPHealNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("MPHealNiagaraComponent"));
	RootComponent = MPHealNiagaraComponent;

	SkillID = ESkillID::BasicMPHeal;
}

void APOSUtilityBasicMPHeal::BeginPlay()
{
	Super::BeginPlay();
	InitTransform();
	return;
}

void APOSUtilityBasicMPHeal::UseSkill()
{
	Super::UseSkill();
	MPHealNiagaraComponent->SetActive(true, true);
	UGameplayStatics::PlaySound2D(this, UsingSound);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("MP Heal : %f"), UtilitySkillData.MPHealAmount));
	}
	return;
}
