// Fill out your copyright notice in the Description page of Project Settings.
#include "../Components/PlayerLookInputComponent.h"

#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "../Components/BasePlayerInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

UPlayerLookInputComponent::UPlayerLookInputComponent()
{

}

void UPlayerLookInputComponent::BindActions(
	UEnhancedInputComponent& InputComponent,
	const UInputAction& InputAction)
{
	Super::BindActions(InputComponent, InputAction);
	InputComponent.BindAction(
		&InputAction,
		ETriggerEvent::Triggered,
		this,
		&UPlayerLookInputComponent::Look
	);
}

void UPlayerLookInputComponent::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void UPlayerLookInputComponent::DoLook(float Yaw, float Pitch)
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!IsValid(OwnerPawn))
	{
		return;
	}

	AController* Controller = OwnerPawn->GetController();
	if (!IsValid(Controller))
	{
		return;
	}

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		OwnerPawn->AddControllerYawInput(Yaw);
		OwnerPawn->AddControllerPitchInput(Pitch);
	}
}
