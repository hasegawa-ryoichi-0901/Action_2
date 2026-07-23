// Fill out your copyright notice in the Description page of Project Settings.
#include "../Components/PlayerMoveInputComponent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Action_2/Action_2.h"

void UPlayerMoveInputComponent::BindActions(
	UEnhancedInputComponent &InputComponent,
	const UInputAction &InputAction)
{
	// UKismetSystemLibrary::PrintString(
	// 	this,
	// 	TEXT("this is MoveInputComponentClass "),
	// 	true,
	// 	true,
	// 	FColor::Cyan,
	// 	2.0f,
	// 	TEXT("None"));

	InputComponent.BindAction(
        &InputAction,
        ETriggerEvent::Triggered,
        this,
        &UPlayerMoveInputComponent::Move
    );
}

void UPlayerMoveInputComponent::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void UPlayerMoveInputComponent::DoMove(float Right, float Forward)
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

    const FRotator ControlRotation =
        Controller->GetControlRotation();

    const FRotator YawRotation(
        0.0f,
        ControlRotation.Yaw,
        0.0f
    );

    const FVector ForwardDirection =
        FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

    const FVector RightDirection =
        FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

    OwnerPawn->AddMovementInput(ForwardDirection, Forward);
    OwnerPawn->AddMovementInput(RightDirection, Right);
}
