// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ESkillType : uint8
{
	Default,
	Attack,
	Utility,
	Life,
	Special,
	Event
};
