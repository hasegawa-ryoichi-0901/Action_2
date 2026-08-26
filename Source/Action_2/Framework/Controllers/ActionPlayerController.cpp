// Fill out your copyright notice in the Description page of Project Settings.


#include "../Framework/Controllers/ActionPlayerController.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetStringLibrary.h"

void AActionPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* enhancedInput =
		Cast<UEnhancedInputComponent>(InputComponent);

	if (!enhancedInput || !toggleDebugMenuAction)
	{
		return;
	}

	enhancedInput->BindAction(
		toggleDebugMenuAction,
		ETriggerEvent::Triggered,
		this,
		&ThisClass::ToggleDebugMenu);
}

void AActionPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AActionPlayerController::ToggleDebugMenu()
{
	// デバッグメニューのClose/Open確認用
	UE_LOG(
		LogTemp,
		Log,
		TEXT("Debug menu is %s"),
		bDebugMenuOpened ? TEXT("Opened") : TEXT("Closed")
	);
	if (this->bDebugMenuOpened)
	{
		this->CloseDebugMenu();
		return;
	}
	this->OpenDebugMenu();
}

void AActionPlayerController::OpenDebugMenu()
{
	if (bDebugMenuOpened)
    {
        return;
    }
	if (!IsValid(this->debugWidget))
	{
		debugWidget = CreateWidget<UDebugRootWidget>(
			this,
			debugWidgetClass);
		if (!IsValid(debugWidget))
		{
			return;
		}
	}

	debugWidget->AddToViewport(1000);
	FInputModeGameAndUI InputMode;

    InputMode.SetWidgetToFocus(
        debugWidget->TakeWidget());

    InputMode.SetHideCursorDuringCapture(false);

    SetInputMode(InputMode);

    debugWidget->SetFocusToFirstItem();

    if (!SetPause(true))
    {
        debugWidget->RemoveFromParent();

        FInputModeGameOnly GameInputMode;
        SetInputMode(GameInputMode);

        return;
    }

    bDebugMenuOpened = true;
}

void AActionPlayerController::CloseDebugMenu()
{
	if (!bDebugMenuOpened)
    {
        return;
    }

    if (IsValid(debugWidget))
    {
        debugWidget->RemoveFromParent();
    }

    FInputModeGameOnly InputMode;
    SetInputMode(InputMode);

    SetPause(false);

    bDebugMenuOpened = false;
}
