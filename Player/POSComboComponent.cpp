// Copyright Epic Games, Inc. All Rights Reserved.

#include "POSComboComponent.h"
#include "GameFramework/Character.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "POSComboPrimaryAsset.h"
#include "TimerManager.h"

UPOSComboComponent::UPOSComboComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPOSComboComponent::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* OwningCharacter = Cast<ACharacter>(GetOwner());
	if (OwningCharacter && OwningCharacter->GetMesh())
	{
		CachedAnimInstance = OwningCharacter->GetMesh()->GetAnimInstance();
	}
}

void UPOSComboComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	CleanupTimer();
}

void UPOSComboComponent::OnAttackInput()
{
	if (!ComboAsset || !CachedAnimInstance.IsValid() || !AttackMontage || ComboAsset->MaxComboCount <= 0)
	{
		return;
	}

	if (bComboFinished)
	{
		return;
	}

	if (ComboState == EPOSComboState::Idle)
	{
		CurrentStepIndex = 0;
		bComboFinished = false;
		PlayComboAnimation();
	}
	else if (ComboState == EPOSComboState::Buffering)
	{
		bInputBuffered = true;
	}
}

void UPOSComboComponent::PlayComboAnimation()
{
	if (!CachedAnimInstance.IsValid() || !AttackMontage)
	{
		return;
	}

	FName SectionName = GetComboSectionName(CurrentStepIndex);
	
	// 애니메이션 재생 및 섹션 점프
	CachedAnimInstance->Montage_Play(AttackMontage, 1.0f, EMontagePlayReturnType::MontageLength, 0.0f, true);
	CachedAnimInstance->Montage_JumpToSection(SectionName, AttackMontage);

	ComboState = EPOSComboState::Playing;
	StartComboWindow();
}

void UPOSComboComponent::StartComboWindow()
{
	CleanupTimer();
	ComboState = EPOSComboState::Buffering;
	float WindowDuration = GetComboWindowDuration(CurrentStepIndex);
	if (WindowDuration > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(
			ComboWindowTimerHandle, 
			this, 
			&UPOSComboComponent::EndComboWindow, 
			WindowDuration, 
			false
		);
	}
	else
	{
		EndComboWindow();
	}
}

void UPOSComboComponent::EndComboWindow()
{
	CleanupTimer();
	if (bInputBuffered)
	{
		bInputBuffered = false;
		CurrentStepIndex += 1;
		if (CurrentStepIndex < GetMaxComboCount())
		{
			PlayComboAnimation();
		}
		else
		{
			bComboFinished = true;
			ComboState = EPOSComboState::Idle;
			
			if (GetWorld())
			{
				GetWorld()->GetTimerManager().SetTimer(
					ComboWindowTimerHandle, 
					this, 
					&UPOSComboComponent::ResetComboFinished, 
					1.0f,
					false
				);
			}
		}
	}
	else
	{
		ComboState = EPOSComboState::Idle;
	}
}

void UPOSComboComponent::ResetComboFinished()
{
	bComboFinished = false;
}

FName UPOSComboComponent::GetComboSectionName(int32 StepIndex) const
{
	if (!ComboAsset)
	{
		return NAME_None;
	}
	return FName(*(ComboAsset->MontageNamePrefix.ToString() + FString::FromInt(StepIndex)));
}

float UPOSComboComponent::GetComboWindowDuration(int32 StepIndex) const
{
	if (!ComboAsset || !ComboAsset->EffectiveFrameCount.IsValidIndex(StepIndex) || ComboAsset->FrameRate <= 0.0f)
	{
		return 0.0f;
	}
	return static_cast<float>(ComboAsset->EffectiveFrameCount[StepIndex]) / ComboAsset->FrameRate;
}

int32 UPOSComboComponent::GetMaxComboCount() const
{
	return ComboAsset ? ComboAsset->MaxComboCount : 0;
}

void UPOSComboComponent::CleanupTimer()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(ComboWindowTimerHandle);
	}
}


