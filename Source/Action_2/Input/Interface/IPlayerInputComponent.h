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
	virtual bool IsPressed() const = 0;
	/// @brief コンポーネントのセットアップ関数
	/// @param InputComponent キャラクターのInputComponentを参照
	virtual  void Setup(UInputComponent& InputComponent) = 0;
	/// @brief バインドされているInputComponentを削除する
	virtual void Teardown() = 0;
};
