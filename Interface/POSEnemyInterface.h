// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "POSEnemyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPOSEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PLEDGEOFSTARLIGHT_API IPOSEnemyInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(Category = "POS|Enemy")
	virtual void TakeDamage(float Damage, float SoundDelay) = 0;

	UFUNCTION(Category = "POS|Enemy")
	virtual USceneComponent* GetHitPoint() = 0;
};
