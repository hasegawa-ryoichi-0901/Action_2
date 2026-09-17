#include "DebugMenuGameplayState.h"

#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"

void FReusableDebugMenuGameplayState::Capture(
	APlayerController* InPlayerController)
{
	if (!IsValid(InPlayerController))
	{
		return;
	}

	if (!PlayerController.IsValid())
	{
		bPreviousMouseCursorVisible = InPlayerController->bShowMouseCursor;
		bPausedBySubsystem = false;
	}

	PlayerController = InPlayerController;
}

void FReusableDebugMenuGameplayState::MarkPausedBySubsystem()
{
	bPausedBySubsystem = true;
}

void FReusableDebugMenuGameplayState::ReleasePause()
{
	if (IsValid(PlayerController.Get()) && bPausedBySubsystem)
	{
		PlayerController->SetPause(false);
	}

	bPausedBySubsystem = false;
}

void FReusableDebugMenuGameplayState::ApplyMenuInputMode(
	const bool bManageInputMode,
	UUserWidget* FocusWidget)
{
	APlayerController* Controller = PlayerController.Get();
	if (!IsValid(Controller) || !bManageInputMode || !IsValid(FocusWidget))
	{
		return;
	}

	FInputModeGameAndUI InputMode;
	InputMode.SetWidgetToFocus(FocusWidget->TakeWidget());
	InputMode.SetHideCursorDuringCapture(false);
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	Controller->SetInputMode(InputMode);
	Controller->bShowMouseCursor = true;
}

void FReusableDebugMenuGameplayState::RestoreInputState(
	const bool bManageInputMode)
{
	APlayerController* Controller = PlayerController.Get();
	if (IsValid(Controller) && bManageInputMode)
	{
		FInputModeGameOnly InputMode;
		Controller->SetInputMode(InputMode);
		Controller->bShowMouseCursor = bPreviousMouseCursorVisible;
	}
}

void FReusableDebugMenuGameplayState::Reset()
{
	PlayerController.Reset();
	bPausedBySubsystem = false;
	bPreviousMouseCursorVisible = false;
}

APlayerController* FReusableDebugMenuGameplayState::GetPlayerController() const
{
	return PlayerController.Get();
}
