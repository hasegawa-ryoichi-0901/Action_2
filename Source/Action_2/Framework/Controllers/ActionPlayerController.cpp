#include "Framework/Controllers/ActionPlayerController.h"

#include "DebugMenuCatalog.h"
#include "DebugMenuSubsystem.h"
#include "DebugMenuTypes.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "ReusableDebugMenu.h"

#define LOCTEXT_NAMESPACE "ActionPlayerControllerDebugMenu"

namespace
{
	constexpr int32 DebugInputMappingContextPriority = 100;
}

void AActionPlayerController::SetupInputComponent()
{
	RemoveDebugMenuInputBinding();
	Super::SetupInputComponent();

#if !UE_BUILD_SHIPPING
	// SetupInputComponent can run before BeginPlay on some controller paths. Retry
	// here so a valid Local Player is enough to make the mapping available.
	RegisterDebugInputMappingContext();

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);
	if (!IsValid(EnhancedInput) || !IsValid(toggleDebugMenuAction))
	{
		return;
	}

	FEnhancedInputActionEventBinding& Binding = EnhancedInput->BindAction(
		toggleDebugMenuAction,
		// Toggle はキーを押している間の毎フレーム通知ではなく、押下開始時に一度だけ処理する。
		ETriggerEvent::Started,
		this,
		&ThisClass::ToggleDebugMenu);
	BoundDebugInputComponent = EnhancedInput;
	DebugMenuBindingHandle = Binding.GetHandle();
#endif
}

void AActionPlayerController::BeginPlay()
{
	Super::BeginPlay();
	RegisterDebugInputMappingContext();
	ConfigureDebugMenu();
}

void AActionPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	RemoveDebugMenuInputBinding();
	RemoveDebugInputMappingContext();
	if (UReusableDebugMenuSubsystem* Subsystem = GetDebugMenuSubsystem())
	{
		Subsystem->NotifyPlayerControllerEndPlay(this);
	}

	Super::EndPlay(EndPlayReason);
}

void AActionPlayerController::RegisterDebugInputMappingContext()
{
#if !UE_BUILD_SHIPPING
	if (!IsValid(debugInputMappingContext))
	{
		UE_LOG(
			LogReusableDebugMenu,
			Warning,
			TEXT("Debug input mapping context is not assigned on '%s'. The debug menu toggle will be unavailable."),
			*GetName());
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = GetEnhancedInputSubsystem();
	if (!IsValid(InputSubsystem))
	{
		UE_LOG(
			LogReusableDebugMenu,
			Warning,
			TEXT("Could not access Enhanced Input subsystem for '%s'; debug mapping context registration will be retried."),
			*GetName());
		return;
	}

	// Do not claim or remove a context registered by another owner.
	if (InputSubsystem->HasMappingContext(debugInputMappingContext))
	{
		return;
	}

	// PlayerInput can be recreated during a map transition while this controller
	// survives. Treat a missing context as a lost registration and add it again.
	bDebugInputMappingContextRegistered = false;
	InputSubsystem->AddMappingContext(debugInputMappingContext, DebugInputMappingContextPriority);
	bDebugInputMappingContextRegistered = InputSubsystem->HasMappingContext(debugInputMappingContext);
	if (!bDebugInputMappingContextRegistered)
	{
		UE_LOG(
			LogReusableDebugMenu,
			Warning,
			TEXT("Failed to register debug input mapping context '%s' for '%s'."),
			*GetNameSafe(debugInputMappingContext),
			*GetName());
	}
#endif
}

void AActionPlayerController::RemoveDebugInputMappingContext()
{
#if !UE_BUILD_SHIPPING
	if (!bDebugInputMappingContextRegistered)
	{
		return;
	}

	if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = GetEnhancedInputSubsystem();
		IsValid(InputSubsystem) && IsValid(debugInputMappingContext))
	{
		InputSubsystem->RemoveMappingContext(debugInputMappingContext);
	}

	bDebugInputMappingContextRegistered = false;
#endif
}

void AActionPlayerController::ToggleDebugMenu()
{
	if (UReusableDebugMenuSubsystem* Subsystem = GetDebugMenuSubsystem())
	{
		Subsystem->ToggleMenu();
	}
}

void AActionPlayerController::ConfigureDebugMenu()
{
#if !UE_BUILD_SHIPPING
	UReusableDebugMenuSubsystem* Subsystem = GetDebugMenuSubsystem();
	if (!IsValid(Subsystem))
	{
		return;
	}

	// カタログの検証失敗時にもデバッグメニュー自体は開けるよう、
	// カタログ登録を Configure から分離してフォールバックを適用する。
	Subsystem->Configure(
		debugWidgetClass,
		nullptr,
		bPauseGameWhenDebugMenuOpen,
		bManageDebugMenuInputMode);

	bool bCatalogRegistered = false;
	if (IsValid(debugMenuCatalog) && debugMenuCatalog->Entries.Num() > 0)
	{
		FText Error;
		bCatalogRegistered = Subsystem->RegisterCatalog(debugMenuCatalog, Error);
		if (!bCatalogRegistered)
		{
			UE_LOG(
				LogReusableDebugMenu,
				Error,
				TEXT("Rejected debug menu catalog '%s': %s. Falling back to default categories."),
				*GetNameSafe(debugMenuCatalog),
				*Error.ToString());
		}
	}

	if (!bCatalogRegistered)
	{
		RegisterFallbackDebugCategories(*Subsystem);
	}
#endif
}

void AActionPlayerController::RegisterFallbackDebugCategories(
	UReusableDebugMenuSubsystem& Subsystem)
{
	TArray<FDebugMenuNodeDefinition> Nodes;
	Nodes.Reserve(6);

	auto AddCategory = [&Nodes](const FName NodeId, const FText& DisplayName, const int32 SortOrder)
	{
		FDebugMenuNodeDefinition& Node = Nodes.AddDefaulted_GetRef();
		Node.NodeId = NodeId;
		Node.DisplayName = DisplayName;
		Node.NodeType = EDebugMenuNodeType::Category;
		Node.SortOrder = SortOrder;
	};

	AddCategory(TEXT("Action2.General"), LOCTEXT("General", "General"), 0);
	AddCategory(TEXT("Action2.Player"), LOCTEXT("Player", "Player"), 10);
	AddCategory(TEXT("Action2.Enemy"), LOCTEXT("Enemy", "Enemy"), 20);
	AddCategory(TEXT("Action2.Combat"), LOCTEXT("Combat", "Combat"), 30);
	AddCategory(TEXT("Action2.Inventory"), LOCTEXT("Inventory", "Inventory"), 40);
	AddCategory(TEXT("Action2.BossAI"), LOCTEXT("BossAI", "Boss AI"), 50);

	FText Error;
	if (!Subsystem.RegisterNodes(Nodes, Error))
	{
		UE_LOG(
			LogReusableDebugMenu,
			Error,
			TEXT("Failed to register Action_2 debug categories: %s"),
			*Error.ToString());
	}
}

void AActionPlayerController::RemoveDebugMenuInputBinding()
{
	if (UEnhancedInputComponent* EnhancedInput = BoundDebugInputComponent.Get();
		IsValid(EnhancedInput) && DebugMenuBindingHandle != 0)
	{
		EnhancedInput->RemoveBindingByHandle(DebugMenuBindingHandle);
	}

	BoundDebugInputComponent.Reset();
	DebugMenuBindingHandle = 0;
}

UEnhancedInputLocalPlayerSubsystem* AActionPlayerController::GetEnhancedInputSubsystem() const
{
	const ULocalPlayer* LocalPlayer = GetLocalPlayer();
	return IsValid(LocalPlayer)
		? LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()
		: nullptr;
}

UReusableDebugMenuSubsystem* AActionPlayerController::GetDebugMenuSubsystem() const
{
	const ULocalPlayer* LocalPlayer = GetLocalPlayer();
	return IsValid(LocalPlayer)
		? LocalPlayer->GetSubsystem<UReusableDebugMenuSubsystem>()
		: nullptr;
}

#undef LOCTEXT_NAMESPACE
