// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PledgeOfStarlight/Struct/POSComboTypes.h"
#include "POSComboComponent.generated.h"

class UAnimMontage;
class UAnimInstance;
class UPOSComboPrimaryAsset;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PLEDGEOFSTARLIGHT_API UPOSComboComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPOSComboComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combo")
	TObjectPtr<UPOSComboPrimaryAsset> ComboAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combo")
	TObjectPtr<UAnimMontage> AttackMontage;

	UFUNCTION(BlueprintCallable, Category="Combo")
	void OnAttackInput();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	EPOSComboState ComboState = EPOSComboState::Idle;
	int32 CurrentStepIndex = 0;
	bool bInputBuffered = false;
	bool bComboFinished = false;

	TWeakObjectPtr<UAnimInstance> CachedAnimInstance;
	FTimerHandle ComboWindowTimerHandle;

	void PlayComboAnimation();
	void StartComboWindow();
	void EndComboWindow();
	void ResetComboFinished();
	
	FName GetComboSectionName(int32 StepIndex) const;
	float GetComboWindowDuration(int32 StepIndex) const;
	int32 GetMaxComboCount() const;
	void CleanupTimer();
};


