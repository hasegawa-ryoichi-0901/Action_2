// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Components/BasePlayerInputComponent.h"
#include "PlayerMoveInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class ACTION_2_API UPlayerMoveInputComponent : public UBasePlayerInputComponent
{
	GENERATED_BODY()

public:
	virtual void Setup() override;
};
