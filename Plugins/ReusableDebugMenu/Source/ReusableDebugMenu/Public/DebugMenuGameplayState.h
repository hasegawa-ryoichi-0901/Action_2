#pragma once

#include "CoreMinimal.h"

class APlayerController;
class UUserWidget;

/**
 * @brief Menu使用中にGameplayの表示・入力状態を退避し、復元します。
 *
 * 意図的にPlain Value Typeとして実装しています。LocalPlayer Subsystemが
 * Lifetimeを所有し、このStateはPlayerControllerへのWeak Referenceだけを保持します。
 * Debug Menuが変更したPause／Input Modeを解放します。
 */
struct REUSABLEDEBUGMENU_API FReusableDebugMenuGameplayState
{
	void Capture(APlayerController* InPlayerController);
	void MarkPausedBySubsystem();
	void ReleasePause();
	void ApplyMenuInputMode(bool bManageInputMode, UUserWidget* FocusWidget);
	void RestoreInputState(bool bManageInputMode);
	void Reset();

	APlayerController* GetPlayerController() const;

private:
	TWeakObjectPtr<APlayerController> PlayerController;
	bool bPausedBySubsystem = false;
	bool bPreviousMouseCursorVisible = false;
};
