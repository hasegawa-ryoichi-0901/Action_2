// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "../../Debug/Widgets/DebugRootWidget.h"
#include "ActionPlayerController.generated.h"
/**
 *
 */
UCLASS()
class ACTION_2_API AActionPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
protected:
	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Debug",
		meta = (AllowPrivateAccess = "true")
	)
	TObjectPtr<UInputAction> toggleDebugMenuAction;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Debug",
		meta = (AllowPrivateAccess = "true")
	)
	TSubclassOf<UDebugRootWidget> debugWidgetClass;

	UPROPERTY(Transient)
	TObjectPtr<UDebugRootWidget> debugWidget;

	bool bDebugMenuOpened = false;

private:
	void ToggleDebugMenu();

	void OpenDebugMenu();

	void CloseDebugMenu();
};
