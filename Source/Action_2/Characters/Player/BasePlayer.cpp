// Fill out your copyright notice in the Description page of Project Settings.
#include "../Player/BasePlayer.h"
#include "EnhancedInputSubsystems.h"

void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();
}

void ABasePlayer::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    DisableMappingContext();
    TeardownPlayerInputComponents();
    Super::EndPlay(EndPlayReason);
}

void ABasePlayer::SetupPlayerInputComponent(class UInputComponent* playerInputComponent)
{
	TeardownPlayerInputComponents();
	Super::SetupPlayerInputComponent(playerInputComponent);
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
		NativeInterface->Setup(*playerInputComponent);
	}
	this->ApplyInputEnabledState();
}

void ABasePlayer::TeardownPlayerInputComponents()
{
    for (TScriptInterface<IPlayerInputComponent>& Entry: PlayerInputComponents)
    {
        if (IPlayerInputComponent* InputInterface =
            Entry.GetInterface())
        {
            InputInterface->Teardown();
        }
    }
    PlayerInputComponents.Reset();
}

void ABasePlayer::ApplyInputEnabledState()
{
	if (this->bInputEnabled)
    {
        EnableMappingContext();
    }
    else
    {
        DisableMappingContext();
    }
}

void ABasePlayer::SetInputEnabled(bool bEnabled)
{
    bInputEnabled = bEnabled;
    ApplyInputEnabledState();
}

UEnhancedInputLocalPlayerSubsystem* ABasePlayer::GetInputSubsystem(AController* controller)
{
    APlayerController* PlayerController =
        Cast<APlayerController>(controller);
    if (!IsValid(PlayerController))
    {
        return nullptr;
    }
    ULocalPlayer* LocalPlayer =
        PlayerController->GetLocalPlayer();
    if (!IsValid(LocalPlayer))
    {
        return nullptr;
    }
    return ULocalPlayer::GetSubsystem<
        UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
}

void ABasePlayer::EnableMappingContext()
{
	if (!IsValid(DefaultMappingContext))
    {
        UE_LOG(
            LogTemp,
            Error,
            TEXT("%s: DefaultMappingContext is not assigned"),
            *GetName()
        );
        return;
    }
	UEnhancedInputLocalPlayerSubsystem* Subsystem =
        GetInputSubsystem(GetController());

    if (!IsValid(Subsystem))
    {
        return;
    }
	 // SetupPlayerInputComponentの再実行に備える
    Subsystem->RemoveMappingContext(DefaultMappingContext);
    Subsystem->AddMappingContext(DefaultMappingContext, 0);
}

void ABasePlayer::DisableMappingContext()
{
	if (!IsValid(DefaultMappingContext))
    {
        return;
    }
    UEnhancedInputLocalPlayerSubsystem* Subsystem =
        GetInputSubsystem(GetController());

	if (IsValid(Subsystem))
    {
        Subsystem->RemoveMappingContext(DefaultMappingContext);
    }
}

void ABasePlayer::UnPossessed()
{
    // Superを呼ぶ前なら、まだ現在のControllerから
    // LocalPlayerSubsystemを取得できる
    DisableMappingContext();
    TeardownPlayerInputComponents();
	Super::UnPossessed();
}