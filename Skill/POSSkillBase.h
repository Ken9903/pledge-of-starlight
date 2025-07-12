// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PledgeOfStarlight/Struct/POSSkillData.h"
#include "POSSkillBase.generated.h"

UCLASS()
class PLEDGEOFSTARLIGHT_API APOSSkillBase : public AActor
{
	GENERATED_BODY()
	
public:
	APOSSkillBase();

	UPROPERTY(Category = "POS|Skill", EditDefaultsOnly)
	ESkillID SkillID; // SubSystem에서 정보를 가져올 수 있음.

	UFUNCTION(Category = "POS|Skill")
	virtual void UseSkill();

protected:
	UPROPERTY(Category = "POS|Skill", VisibleAnywhere)
	FSkillData SkillData;

	UPROPERTY(Category = "POS|Skill", EditDefaultsOnly)
	FVector3d AttachPosition;

	UPROPERTY(Category = "POS|Skill", EditDefaultsOnly)
	FRotator AttachRotation;

	UPROPERTY(Category = "POS|Sound", EditDefaultsOnly)
	TObjectPtr<USoundWave> UsingSound;

	virtual void BeginPlay() override;

	UFUNCTION(Category = "POS|Skill")
	void InitTransform();

private:
	void SendSkillIDToInteractGimmick();

};
