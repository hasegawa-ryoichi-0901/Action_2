#include "Framework/Controllers/ActionPlayerController.h"

#include "DebugMenuCatalog.h"
#include "DebugMenuSubsystem.h"
#include "DebugMenuTypes.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "ReusableDebugMenu.h"

#define LOCTEXT_NAMESPACE "ActionPlayerControllerDebugMenu"

void AActionPlayerController::SetupInputComponent()
{
	RemoveDebugMenuInputBinding();
	Super::SetupInputComponent();

#if !UE_BUILD_SHIPPING
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
	ConfigureDebugMenu();
}

void AActionPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	RemoveDebugMenuInputBinding();
	if (UReusableDebugMenuSubsystem* Subsystem = GetDebugMenuSubsystem())
	{
		Subsystem->NotifyPlayerControllerEndPlay(this);
	}

	Super::EndPlay(EndPlayReason);
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

UReusableDebugMenuSubsystem* AActionPlayerController::GetDebugMenuSubsystem() const
{
	const ULocalPlayer* LocalPlayer = GetLocalPlayer();
	return IsValid(LocalPlayer)
		? LocalPlayer->GetSubsystem<UReusableDebugMenuSubsystem>()
		: nullptr;
}

#undef LOCTEXT_NAMESPACE
