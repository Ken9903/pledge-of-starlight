// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PledgeOfStarlight/Interface/POSGimmickInteractInterface.h"
#include "PledgeOfStarlight/Struct/POSGimmickObjectInfo.h"
#include "POSGimmickObjectBase.generated.h"

UCLASS()
class PLEDGEOFSTARLIGHT_API APOSGimmickObjectBase : public AActor, public IPOSGimmickInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APOSGimmickObjectBase();

	virtual void InteractSkill(FName SkillID) override;

protected:
	UPROPERTY(Category = "POS|Gimmick", EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;


	UPROPERTY(Category = "POS|Gimmick", EditDefaultsOnly, BlueprintReadOnly)
	FName GimmickObjectID;

	UPROPERTY(Category = "POS|Gimmick", VisibleAnywhere, BlueprintReadOnly)
	FPOSGimmickObjectInfo GimmickObjectInfo;

	UPROPERTY(Category = "POS|Gimmick", VisibleAnywhere, BlueprintReadOnly) //TODO : Save
	TMap<FName, bool> GimmickSuccessMap;

	//대화클릭시 true로 변경.
	UPROPERTY(Category = "POS|Gimmick", VisibleAnywhere, BlueprintReadOnly)//TODO : Save
	TMap<FName, bool> GimmickExecutionMap;

	//Gimmick Data Save Check
	UPROPERTY(Category = "POS|Gimmick", VisibleAnywhere, BlueprintReadOnly)//TODO : Save
	uint8 isSaved : 1 = false;

	virtual void BeginPlay() override;

	void InitGimmickMap(); // 저장된 데이터가 없을 경우 실행.

};
