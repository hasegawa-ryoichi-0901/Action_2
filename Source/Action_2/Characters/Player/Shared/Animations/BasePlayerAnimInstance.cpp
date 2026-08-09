// Fill out your copyright notice in the Description page of Project Settings.


#include "../Animations/BasePlayerAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

void UBasePlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	ABasePlayer* CachedBasePlayer = Cast<ABasePlayer>(TryGetPawnOwner());
	if (!IsValid(CachedBasePlayer))
	{
		UE_LOG(
			LogTemp,
			Error,
			TEXT("%s: TryGetPawnOwner() is not [ABasePlayer]. GetPawn=%s"),
			*GetName(),
			*GetNameSafe(CachedBasePlayer));
		return;
	}
	basePlayer = CachedBasePlayer;
}

void UBasePlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	OnAnimationUpdated(DeltaSeconds);
	if (!IsValid(basePlayer))
	{
		return;
	}
	this->SetGroundSpeed();
	this->SetShouldMove();
}

void UBasePlayerAnimInstance::SetGroundSpeed()
{
	const UMovementComponent* movementComponent = basePlayer->GetMovementComponent();
	const FVector Velocity = movementComponent->Velocity;
	this->groundSpeed = Velocity.Size2D();
}

void UBasePlayerAnimInstance::SetShouldMove()
{
	UCharacterMovementComponent* movementComponent = basePlayer->GetCharacterMovement();
	const FVector acceleration = movementComponent->GetCurrentAcceleration();
    const bool bHasAcceleration = !acceleration.IsNearlyZero();
	this->shouldMove = this->groundSpeed > this->minGroundSpeedToMove && bHasAcceleration;
}
