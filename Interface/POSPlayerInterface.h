// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PledgeOfStarlight/Widget/POSNPCDialogueHighlightWidget.h"
#include "UObject/Interface.h"
#include "POSPlayerInterface.generated.h"

class UPOSPlayerAbility;
class UPOSPlayerInventory;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPOSPlayerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PLEDGEOFSTARLIGHT_API IPOSPlayerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//PlayerAbility
	virtual UPOSPlayerAbility* GetPlayerAbility() = 0;

	//PlayerInventory
	virtual UPOSPlayerInventory* GetPlayerInventory() = 0;


	//Dialogue
	virtual UPOSNPCDialogueHighlightWidget* GetNPCDialogueHighlightWidget() = 0;
	virtual void SetNPCDialogueHighlightWidget(UPOSNPCDialogueHighlightWidget* InNPCDialogueHighlightWidget) = 0;
	
};
