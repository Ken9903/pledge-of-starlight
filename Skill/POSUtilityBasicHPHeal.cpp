// Fill out your copyright notice in the Description page of Project Settings.


#include "POSUtilityBasicHPHeal.h"

#include "Kismet/GameplayStatics.h"

APOSUtilityBasicHPHeal::APOSUtilityBasicHPHeal()
{
	HPHealNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("HPHealNiagaraComponent"));
	RootComponent = HPHealNiagaraComponent;
	SkillID = ESkillID::BasicHPHeal;
}

void APOSUtilityBasicHPHeal::BeginPlay()
{
	Super::BeginPlay();
	InitTransform();
	return;
}

void APOSUtilityBasicHPHeal::UseSkill()
{
	Super::UseSkill();
	HPHealNiagaraComponent->SetActive(true, true);
	UGameplayStatics::PlaySound2D(this, UsingSound);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("HP Heal : %f"), UtilitySkillData.HPHealAmount));
	}
	return;
}
