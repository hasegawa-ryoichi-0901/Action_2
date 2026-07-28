// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Components/BasePlayerInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerMoveInputComponent.generated.h"

/**
 *
 */
UCLASS()
class ACTION_2_API UPlayerMoveInputComponent : public UBasePlayerInputComponent
{
	GENERATED_BODY()

protected:
	/// @brief Inputにバインドするための関数
	/// @param Value EnhancedInputの構造体
	virtual void Move(const FInputActionValue& Value);
	/// @brief このコンポーネントを所持しているアクターの移動制御ロジック
	/// @param Right 左右の正規化
	/// @param Forward 前後ろの正規化
	virtual void DoMove(float Right, float Forward);
	virtual void BindActions(
		UEnhancedInputComponent& InputComponent,
		const UInputAction& InputAction
    ) override;
};
