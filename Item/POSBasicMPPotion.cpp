// Fill out your copyright notice in the Description page of Project Settings.


#include "POSBasicMPPotion.h"

APOSBasicMPPotion::APOSBasicMPPotion()
{
	ItemID = EItemID::BasicMPPosion;
}

void APOSBasicMPPotion::UseItem()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("MP Heal : %d Use Item"), ConsumableItemData.MPHealAmount));
	}
	return;
}
