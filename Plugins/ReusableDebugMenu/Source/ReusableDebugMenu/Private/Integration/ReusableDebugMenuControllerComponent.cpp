#include "Integration/ReusableDebugMenuControllerComponent.h"

#include "DebugMenuCatalog.h"
#include "DebugMenuSubsystem.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedPlayerInput.h"
#include "GameFramework/PlayerController.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "Integration/ReusableDebugMenuInputMatcher.h"
#include "ReusableDebugMenu.h"
#include "UI/DebugMenuRootWidget.h"

void UReusableDebugMenuControllerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (bAutoInitialize)
	{
		InitializeDebugMenu();
	}
}

void UReusableDebugMenuControllerComponent::EndPlay(
	const EEndPlayReason::Type EndPlayReason)
{
	UnbindInput();
	RemoveMappingContext();

	if (UReusableDebugMenuSubsystem* Subsystem = GetDebugMenuSubsystem())
	{
		if (VisibilityChangedHandle.IsValid())
		{
			Subsystem->OnVisibilityChanged().Remove(VisibilityChangedHandle);
			VisibilityChangedHandle.Reset();
		}

		if (Subsystem->OnToggleInputRequested().IsBoundToObject(this))
		{
			Subsystem->OnToggleInputRequested().Unbind();
		}
		Subsystem->NotifyPlayerControllerEndPlay(GetOwnerPlayerController());
	}

	bInitialized = false;
	Super::EndPlay(EndPlayReason);
}

bool UReusableDebugMenuControllerComponent::InitializeDebugMenu()
{
	bInitialized = false;

	APlayerController* PlayerController = GetOwnerPlayerController();
	if (!IsValid(PlayerController))
	{
		UE_LOG(
			LogReusableDebugMenu,
			Warning,
			TEXT("ReusableDebugMenuControllerComponent must be owned by a PlayerController."));
		return false;
	}

	UReusableDebugMenuSubsystem* Subsystem = GetDebugMenuSubsystem();
	if (!IsValid(Subsystem))
	{
		UE_LOG(
			LogReusableDebugMenu,
			Warning,
			TEXT("Could not resolve the local debug menu subsystem for '%s'."),
			*GetNameSafe(PlayerController));
		return false;
	}

	if (!MenuWidgetClass || MenuWidgetClass->HasAnyClassFlags(CLASS_Abstract))
	{
		UE_LOG(
			LogReusableDebugMenu,
			Error,
			TEXT("Debug menu root widget class is missing or abstract on '%s'."),
			*GetNameSafe(this));
		return false;
	}

	UnbindInput();
	if (!RegisterMappingContext())
	{
		return false;
	}

	if (!BindInput())
	{
		RemoveMappingContext();
		return false;
	}

	Subsystem->OnToggleInputRequested().BindUObject(
		this,
		&ThisClass::MatchesToggleInput);
	Subsystem->Configure(
		MenuWidgetClass,
		nullptr,
		bPauseGameWhenOpen,
		bManageInputMode);

	if (IsValid(Catalog))
	{
		FText Error;
		if (!Subsystem->RegisterCatalog(Catalog, Error))
		{
			UE_LOG(
				LogReusableDebugMenu,
				Error,
				TEXT("Rejected debug menu catalog '%s': %s"),
				*GetNameSafe(Catalog),
				*Error.ToString());
			UnbindInput();
			RemoveMappingContext();
			if (Subsystem->OnToggleInputRequested().IsBoundToObject(this))
			{
				Subsystem->OnToggleInputRequested().Unbind();
			}
			return false;
		}
	}

	if (!VisibilityChangedHandle.IsValid())
	{
		VisibilityChangedHandle = Subsystem->OnVisibilityChanged().AddUObject(
			this,
			&ThisClass::HandleVisibilityChanged);
	}

	bInitialized = true;
	return true;
}

void UReusableDebugMenuControllerComponent::ToggleDebugMenu()
{
	if ((!bInitialized && !InitializeDebugMenu()) || !IsValid(GetDebugMenuSubsystem()))
	{
		return;
	}

	GetDebugMenuSubsystem()->ToggleMenu();
}

void UReusableDebugMenuControllerComponent::ShowDebugMenu()
{
	if ((!bInitialized && !InitializeDebugMenu()) || !IsValid(GetDebugMenuSubsystem()))
	{
		return;
	}

	GetDebugMenuSubsystem()->ShowMenu();
}

void UReusableDebugMenuControllerComponent::HideDebugMenu()
{
	if (UReusableDebugMenuSubsystem* Subsystem = GetDebugMenuSubsystem())
	{
		Subsystem->HideMenu();
	}
}

bool UReusableDebugMenuControllerComponent::IsDebugMenuOpen() const
{
	const UReusableDebugMenuSubsystem* Subsystem = GetDebugMenuSubsystem();
	return IsValid(Subsystem) && Subsystem->IsMenuOpen();
}

bool UReusableDebugMenuControllerComponent::BindInput()
{
	APlayerController* PlayerController = GetOwnerPlayerController();
	UEnhancedInputComponent* EnhancedInput = IsValid(PlayerController)
		? Cast<UEnhancedInputComponent>(PlayerController->InputComponent)
		: nullptr;

	if (!IsValid(EnhancedInput) || !IsValid(ToggleMenuAction))
	{
		UE_LOG(
			LogReusableDebugMenu,
			Warning,
			TEXT("Debug menu input binding is unavailable on '%s'."),
			*GetNameSafe(this));
		return false;
	}

	FEnhancedInputActionEventBinding& Binding = EnhancedInput->BindAction(
		ToggleMenuAction,
		ETriggerEvent::Started,
		this,
		&ThisClass::ToggleDebugMenu);

	BoundInputComponent = EnhancedInput;
	InputBindingHandle = Binding.GetHandle();
	return InputBindingHandle != 0;
}

void UReusableDebugMenuControllerComponent::UnbindInput()
{
	if (UEnhancedInputComponent* EnhancedInput = BoundInputComponent.Get();
		IsValid(EnhancedInput) && InputBindingHandle != 0)
	{
		EnhancedInput->RemoveBindingByHandle(InputBindingHandle);
	}

	BoundInputComponent.Reset();
	InputBindingHandle = 0;
}

bool UReusableDebugMenuControllerComponent::RegisterMappingContext()
{
	if (!IsValid(DebugInputMappingContext))
	{
		UE_LOG(
			LogReusableDebugMenu,
			Warning,
			TEXT("Debug input mapping context is not assigned on '%s'."),
			*GetNameSafe(this));
		return false;
	}

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = GetEnhancedInputSubsystem();
	if (!IsValid(InputSubsystem))
	{
		UE_LOG(
			LogReusableDebugMenu,
			Warning,
			TEXT("Could not resolve Enhanced Input subsystem for '%s'."),
			*GetNameSafe(this));
		return false;
	}

	if (InputSubsystem->HasMappingContext(DebugInputMappingContext))
	{
		return true;
	}

	bMappingContextRegistered = false;
	InputSubsystem->AddMappingContext(DebugInputMappingContext, MappingContextPriority);
	bMappingContextRegistered = InputSubsystem->HasMappingContext(DebugInputMappingContext);
	return bMappingContextRegistered;
}

void UReusableDebugMenuControllerComponent::RemoveMappingContext()
{
	if (!bMappingContextRegistered)
	{
		return;
	}

	if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = GetEnhancedInputSubsystem();
		IsValid(InputSubsystem) && IsValid(DebugInputMappingContext))
	{
		InputSubsystem->RemoveMappingContext(DebugInputMappingContext);
	}

	bMappingContextRegistered = false;
}

void UReusableDebugMenuControllerComponent::HandleVisibilityChanged(
	const bool bIsMenuOpen)
{
	OnMenuVisibilityChanged.Broadcast(bIsMenuOpen);
}

bool UReusableDebugMenuControllerComponent::MatchesToggleInput(
	const FKeyEvent& KeyEvent) const
{
	if (!IsValid(ToggleMenuAction))
	{
		return false;
	}

	const UEnhancedInputLocalPlayerSubsystem* InputSubsystem = GetEnhancedInputSubsystem();
	const UEnhancedPlayerInput* EnhancedPlayerInput = IsValid(InputSubsystem)
		? InputSubsystem->GetPlayerInput()
		: nullptr;

	if (!IsValid(EnhancedPlayerInput) || !IsValid(InputSubsystem) ||
		!FReusableDebugMenuInputMatcher::Matches(
			*ToggleMenuAction,
			*EnhancedPlayerInput,
			*InputSubsystem,
			KeyEvent))
	{
		return false;
	}

	return true;
}

APlayerController* UReusableDebugMenuControllerComponent::GetOwnerPlayerController() const
{
	return Cast<APlayerController>(GetOwner());
}

UEnhancedInputLocalPlayerSubsystem*
UReusableDebugMenuControllerComponent::GetEnhancedInputSubsystem() const
{
	const APlayerController* PlayerController = GetOwnerPlayerController();
	const ULocalPlayer* LocalPlayer = IsValid(PlayerController)
		? PlayerController->GetLocalPlayer()
		: nullptr;

	return IsValid(LocalPlayer)
		? LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()
		: nullptr;
}

UReusableDebugMenuSubsystem*
UReusableDebugMenuControllerComponent::GetDebugMenuSubsystem() const
{
	const APlayerController* PlayerController = GetOwnerPlayerController();
	const ULocalPlayer* LocalPlayer = IsValid(PlayerController)
		? PlayerController->GetLocalPlayer()
		: nullptr;

	return IsValid(LocalPlayer)
		? LocalPlayer->GetSubsystem<UReusableDebugMenuSubsystem>()
		: nullptr;
}
