// Fill out your copyright notice in the Description page of Project Settings.
#include "../Player/BasePlayer.h"
#include "EnhancedInputSubsystems.h"
void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();
}

void ABasePlayer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponents.Reset();
    TInlineComponentArray<UBasePlayerInputComponent*> AttachedComponents(this);
	for (UBasePlayerInputComponent* Component : AttachedComponents)
	{
	    if (!IsValid(Component))
	    {
	        continue;
	    }

	    IPlayerInputComponent* NativeInterface =
	        Cast<IPlayerInputComponent>(Component);

	    if (!NativeInterface)
	    {
	        continue;
	    }

	    TScriptInterface<IPlayerInputComponent> InterfaceEntry;
	    InterfaceEntry.SetObject(Component);
	    InterfaceEntry.SetInterface(NativeInterface);

	    PlayerInputComponents.Add(InterfaceEntry);
	    NativeInterface->Setup(PlayerInputComponent);
	}
	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (APlayerController* PlayerController = Cast<APlayerController>(controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}
