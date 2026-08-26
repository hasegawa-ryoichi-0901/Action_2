// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Misc/EnumRange.h"

UENUM(BlueprintType)
enum class EDebugMenuCategory : uint8
{
	General,
    Player,
    Enemy,
    Combat,
    Inventory,
    BossAI,

	Count UMETA(Hidden)
};

ENUM_RANGE_BY_COUNT(
    EDebugMenuCategory,
    EDebugMenuCategory::Count);

UENUM()
enum class EDebugMenuPlayerListType : uint8
{
	General,
	Position,

	Count UMETA(Hidden)
};

ENUM_RANGE_BY_COUNT(
    EDebugMenuPlayerListType,
    EDebugMenuPlayerListType::Count);
