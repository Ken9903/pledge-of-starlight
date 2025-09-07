// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "POSComboPrimaryAsset.generated.h"

UCLASS(BlueprintType)
class PLEDGEOFSTARLIGHT_API UPOSComboPrimaryAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(Category = "POS|Animation", EditAnywhere, BlueprintReadOnly)
	FName MontageNamePrefix = TEXT("Combo_");
	
	UPROPERTY(Category = "POS|Animation", EditAnywhere, BlueprintReadOnly)
	int32 MaxComboCount = 3;
	
	UPROPERTY(Category = "POS|Animation", EditAnywhere, BlueprintReadOnly)
	float FrameRate = 30.0f;
	
	UPROPERTY(Category = "POS|Animation", EditAnywhere, BlueprintReadOnly)
	TArray<int32> EffectiveFrameCount;
};

