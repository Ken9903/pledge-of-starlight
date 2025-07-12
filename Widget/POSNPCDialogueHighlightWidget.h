// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueBuilderObject.h"
#include "Blueprint/UserWidget.h"
#include "POSNPCDialogueHighlightWidget.generated.h"

/**
 * 
 */
UCLASS()
class PLEDGEOFSTARLIGHT_API UPOSNPCDialogueHighlightWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(Category = "POS|Scenario", VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UDialogueBuilderObject> DialogueContent;
	
};
