// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../../BasePlayer.h"
#include "BasePlayerAnimInstance.generated.h"

/**
 *
 */
UCLASS(BlueprintType, Blueprintable, Abstract)
class ACTION_2_API UBasePlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Animation")
	void OnAnimationUpdated(float DeltaSeconds);

	/// @brief 初期化関数
	virtual void NativeInitializeAnimation() override;

	/// @brief 更新処理関数
	/// @param DeltaSeconds
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	/// @brief 地上アニメーション速度の設定
	virtual void SetGroundSpeed();

	/// @brief 移動が可能か判定
	virtual void SetShouldMove();

	/// @brief 地上速度
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation|Movement")
	float groundSpeed = 0;

	/// @brief 移動可能か
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation|Movement")
	bool shouldMove = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Class)
	ABasePlayer* basePlayer;

	UPROPERTY(
	EditDefaultsOnly,
	BlueprintReadOnly,
	Category = "Animation|Movement",
	meta = (ClampMin = "0.0", ForceUnits = "cm/s"))
	float minGroundSpeedToMove = 0.01f;
};
