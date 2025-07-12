// Fill out your copyright notice in the Description page of Project Settings.


#include "POSSaveLoadGameInstanceSubsystem.h"

#include "POSSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "PledgeOfStarlight/Skill/POSSkillGameInstanceSubSystem.h"

void UPOSSaveLoadGameInstanceSubsystem::SaveEarnedSkillList()
{
	CheckPlayer();
	UPOSSaveGame* SaveGameInstance = Cast<UPOSSaveGame>(UGameplayStatics::CreateSaveGameObject(UPOSSaveGame::StaticClass()));
	UPOSSkillGameInstanceSubSystem* POSSkillSubsystem = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UPOSSkillGameInstanceSubSystem>();
	SaveGameInstance->EarnedSkillDataList = POSSkillSubsystem->GetEarnedSkillDataList();
	if(UGameplayStatics::SaveGameToSlot(SaveGameInstance, EarnedSkillListSlotName, 0))
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Earned Skill Data Save Success"));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Earned Skill Data Save Fail"));
		}
	}
	return;
}

void UPOSSaveLoadGameInstanceSubsystem::LoadEarnedSkillList()
{
	CheckPlayer();
	if(UGameplayStatics::DoesSaveGameExist(EarnedSkillListSlotName, 0))
	{
		UPOSSaveGame* SaveGameInstance = Cast<UPOSSaveGame>(UGameplayStatics::LoadGameFromSlot(EarnedSkillListSlotName, 0));
		if(SaveGameInstance)
		{
			UPOSSkillGameInstanceSubSystem* POSSkillSubsystem = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UPOSSkillGameInstanceSubSystem>();
			POSSkillSubsystem->GetEarnedSkillDataList() = SaveGameInstance->EarnedSkillDataList;
			
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Earned Skill Load Success"));
			}
			return;
		}
	}
	else
	{
		SaveEarnedSkillList();
		
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Skill Name New Save Data"));
		}
		return;
	}
}

void UPOSSaveLoadGameInstanceSubsystem::SavePresetList()
{
	CheckPlayer();
	UPOSSaveGame* SaveGameInstance = Cast<UPOSSaveGame>(UGameplayStatics::CreateSaveGameObject(UPOSSaveGame::StaticClass()));
	SaveGameInstance->PresetDataList = POSPlayer->GetPlayerAbility()->GetPresetDataList();
	if(UGameplayStatics::SaveGameToSlot(SaveGameInstance, PresetSkillListSlotName, 0))
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Preset Skill Save Success"));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Preset Skill Preset Save Faill"));
		}
	}
	return;
}

void UPOSSaveLoadGameInstanceSubsystem::LoadPresetList()
{
	CheckPlayer();
	if(UGameplayStatics::DoesSaveGameExist(PresetSkillListSlotName, 0))
	{
		UPOSSaveGame* SaveGameInstance = Cast<UPOSSaveGame>(UGameplayStatics::LoadGameFromSlot(PresetSkillListSlotName, 0));
		if(SaveGameInstance)
		{
			POSPlayer->GetPlayerAbility()->SetPresetDataList(SaveGameInstance->PresetDataList);
			
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Preset Skill Load Success"));
			}
			return;
		}
	}
	else
	{
		SavePresetList();
		
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Skill Preset New Save Data"));
		}
		return;
	}
}

void UPOSSaveLoadGameInstanceSubsystem::SaveInventory()
{
	CheckPlayer();
	UPOSSaveGame* SaveGameInstance = Cast<UPOSSaveGame>(UGameplayStatics::CreateSaveGameObject(UPOSSaveGame::StaticClass()));
	SaveGameInstance->InventoryDataList = POSPlayer->GetPlayerInventory()->GetInventoryItemDataList();
	if(UGameplayStatics::SaveGameToSlot(SaveGameInstance, InventorySlotName, 0))
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Inventory Save Success"));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Inventory Data Save Faill"));
		}
	}
	return;
}

void UPOSSaveLoadGameInstanceSubsystem::LoadInventory()
{
	CheckPlayer();
	if(UGameplayStatics::DoesSaveGameExist(InventorySlotName, 0))
	{
		UPOSSaveGame* SaveGameInstance = Cast<UPOSSaveGame>(UGameplayStatics::LoadGameFromSlot(InventorySlotName, 0));
		if(SaveGameInstance)
		{
			POSPlayer->GetPlayerInventory()->SetInventoryItemDataList(SaveGameInstance->InventoryDataList);
			
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Inventory Load Success"));
			}
			return;
		}
	}
	else
	{
		SaveInventory();
		
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Inventory New Save Data"));
		}
		return;
	}
}

void UPOSSaveLoadGameInstanceSubsystem::CheckPlayer()
{
	if(!IsValid(POSPlayer))
	{
		InitPlayer();
	}
	return;
}

void UPOSSaveLoadGameInstanceSubsystem::InitPlayer()
{
	POSPlayer = Cast<APledgeOfStarlightCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	return;
}
