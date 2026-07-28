// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Components/BasePlayerInputComponent.h"
#include "PlayerLookInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class ACTION_2_API UPlayerLookInputComponent : public UBasePlayerInputComponent
{
	GENERATED_BODY()

	UPlayerLookInputComponent();
protected:
	void BindActions(
		UEnhancedInputComponent& InputComponent,
		const UInputAction& InputAction
    ) override;

private:
	void Look(const FInputActionValue& Value);
	void DoLook(float Yaw, float Pitch);
};
