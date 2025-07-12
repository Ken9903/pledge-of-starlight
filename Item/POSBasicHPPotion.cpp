// Fill out your copyright notice in the Description page of Project Settings.


#include "POSBasicHPPotion.h"

APOSBasicHPPotion::APOSBasicHPPotion()
{
	ItemID = EItemID::BasicHPPosion;
}

void APOSBasicHPPotion::UseItem()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("HP Heal : %d Use Item"), ConsumableItemData.HPHealAmount));
	}
	return;
}
