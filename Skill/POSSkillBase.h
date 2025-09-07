
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PledgeOfStarlight/Struct/POSSkillData.h"
#include "Animation/AnimMontage.h"
#include "POSSkillBase.generated.h"

class APledgeOfStarlightCharacter;

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

	UPROPERTY(Category = "POS|Animation", EditDefaultsOnly)
	TObjectPtr<UAnimMontage> SkillMontage;

	virtual void BeginPlay() override;
	
	UPROPERTY()
	TWeakObjectPtr<APledgeOfStarlightCharacter> CachedPlayerCharacter;

	UFUNCTION(Category = "POS|Skill")
	void InitTransform();

private:
	void SendSkillIDToInteractGimmick();

};
