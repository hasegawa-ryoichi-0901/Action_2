// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "../Debug/EDebugMenuCategory.h"
#include "../Debug/Widgets/DebugRootWidget.h"
#include "../Debug/Widgets/Windows/BaseDebugWindow.h"
#include "DebugUISubsystem.generated.h"

/**
 *
 */
UCLASS(BlueprintType, Blueprintable, Abstract)
class ACTION_2_API UDebugUISubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()
public:
	void ShowMenu();
	void HideMenu();

	/// @brief 該当デバッグウィンドウの表示切替
	/// @param listType enum
	/// @param bEnabled
	void SetDebugWindowEnabled(
		EDebugMenuCategory listType,
		bool bEnabled);

	/// @brief
	/// @param listType
	/// @return bool
	bool IsDebugWindowEnabled(
		EDebugMenuCategory listType) const;

private:
	UPROPERTY(Transient)
	TObjectPtr<UDebugRootWidget> MenuWidget;

	UPROPERTY(Transient)
	TMap<
		EDebugMenuCategory,
		TObjectPtr<UBaseDebugWindow>>
		ActiveDebugWindows;
};
