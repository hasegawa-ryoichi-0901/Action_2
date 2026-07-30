// Fill out your copyright notice in the Description page of Project Settings.
#include "../Player/BasePlayer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "../../Characters/BaseCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Components/ArrowComponent.h"

ABasePlayer::ABasePlayer()
{
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

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

		const FGameplayTag& newInputTag = NativeInterface->GetTaggedInputAction().InputTag;
		if (!newInputTag.IsValid())
		{
			UE_LOG(
				LogTemp,
				Error,
				TEXT("%s: InputTag is not assigned. Component=%s"),
				*GetName(),
				*GetNameSafe(Component));
			continue;
		}
		const bool bHasDuplicateInputTag = PlayerInputComponents.Contains(newInputTag);
		if (bHasDuplicateInputTag)
		{
			UE_LOG(
				LogTemp,
				Error,
				TEXT("%s: Duplicate InputTag '%s'. Component=%s"),
				*GetName(),
				*newInputTag.ToString(),
				*GetNameSafe(Component));
			continue;
		}

		TScriptInterface<IPlayerInputComponent> InterfaceEntry;
		InterfaceEntry.SetObject(Component);
		InterfaceEntry.SetInterface(NativeInterface);
		PlayerInputComponents.Add(InterfaceEntry->GetTaggedInputAction().InputTag, InterfaceEntry);
		NativeInterface->Setup(*playerInputComponent);
	}
	this->ApplyInputEnabledState();
}

void ABasePlayer::TeardownPlayerInputComponents()
{
	for (TPair<FGameplayTag, TScriptInterface<IPlayerInputComponent>>& Entry : PlayerInputComponents)
	{
		if (IPlayerInputComponent* InputInterface =
			Entry.Value.GetInterface())
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
