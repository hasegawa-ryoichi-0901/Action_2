// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Kismet/GameplayStatics.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "../FTaggedInputAction.h"
#include "IPlayerInputComponent.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType, Blueprintable, MinimalAPI)
class UPlayerInputComponent : public UInterface
{
	GENERATED_BODY()
};

/**
 * キー入力インターフェース
 */
class ACTION_2_API IPlayerInputComponent
{
	GENERATED_BODY()
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual const FTaggedInputAction& GetTaggedInputAction() const = 0;
	virtual const bool& IsPressed() const = 0;
public:
	virtual  void Setup(UInputComponent* InputComponent) = 0;
	/* キーを押下した際の制御 */
	virtual void HandlePressedAction() = 0;
	/* キーを離した際の制御 */
	virtual void HandleReleasedAction() = 0;
	/*Input有効化*/
	virtual  void Enable(APlayerController& controller) = 0;
	/*Input無効化*/
	virtual  void Disable(APlayerController& controller) = 0;
};
