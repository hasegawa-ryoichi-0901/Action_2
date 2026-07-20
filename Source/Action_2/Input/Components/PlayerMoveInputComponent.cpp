// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/KismetSystemLibrary.h"
#include "../Components/PlayerMoveInputComponent.h"

void UPlayerMoveInputComponent::Setup(){
	UKismetSystemLibrary::PrintString(
		this,
		TEXT("this is MoveInputComponentClass "),
		true,
		true,
		FColor::Cyan,
		2.0f,
		TEXT("None"));
}