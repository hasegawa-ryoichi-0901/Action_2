// Fill out your copyright notice in the Description page of Project Settings.
#include "../Player/BasePlayer.h"

void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();
}

void ABasePlayer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponents.Reset();

    TInlineComponentArray<UActorComponent*> AttachedComponents(this);

    for (UActorComponent* Component : AttachedComponents)
    {
        if (!IsValid(Component) ||
            !Component->Implements<UPlayerInputComponent>())
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
        NativeInterface->Setup();
    }
}