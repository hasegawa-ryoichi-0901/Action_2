#include "DebugMenuSubsystem.h"

#include "DebugMenuCatalog.h"
#include "DebugMenuRegistry.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/PlayerController.h"
#include "ReusableDebugMenu.h"
#include "UI/DebugMenuRootWidget.h"
#include "UI/DebugMenuWindow.h"
#include "Window/ReusableDebugMenuWindowManager.h"

void UReusableDebugMenuSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Registry = NewObject<UReusableDebugMenuRegistry>(this);
	WindowManager = NewObject<UReusableDebugMenuWindowManager>(this);
	WindowManager->Initialize(Registry);
}

void UReusableDebugMenuSubsystem::Deinitialize()
{
	CloseAllWindows();
	HideMenu();
	WindowManager = nullptr;
	MenuWidget = nullptr;
	Registry = nullptr;
	Super::Deinitialize();
}

bool UReusableDebugMenuSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
#if UE_BUILD_SHIPPING
	return false;
#else
	return Super::ShouldCreateSubsystem(Outer);
#endif
}

void UReusableDebugMenuSubsystem::Configure(
	TSubclassOf<UReusableDebugMenuRootWidget> InMenuWidgetClass,
	const UReusableDebugMenuCatalog* InCatalog,
	const bool bInPauseGameWhenOpen,
	const bool bInManageInputMode)
{
	if ((bMenuOpen || HasActiveDebugWindows()) &&
		(MenuWidgetClass != InMenuWidgetClass ||
		 bPauseGameWhenOpen != bInPauseGameWhenOpen ||
		 bManageInputMode != bInManageInputMode))
	{
		CloseAllWindows();
		HideMenu();
		if (MenuWidgetClass != InMenuWidgetClass)
		{
			MenuWidget = nullptr;
		}
	}

	MenuWidgetClass = InMenuWidgetClass;
	bPauseGameWhenOpen = bInPauseGameWhenOpen;
	bManageInputMode = bInManageInputMode;

	if (IsValid(InCatalog))
	{
		FText Error;
		if (!RegisterCatalog(InCatalog, Error))
		{
			UE_LOG(
				LogReusableDebugMenu,
				Error,
				TEXT("Rejected debug menu catalog '%s': %s"),
				*GetNameSafe(InCatalog),
				*Error.ToString());
		}
	}
}

bool UReusableDebugMenuSubsystem::RegisterNode(
	const FDebugMenuNodeDefinition& Node,
	FText& OutError)
{
	return RegisterNodes({Node}, OutError);
}

bool UReusableDebugMenuSubsystem::RegisterNodes(
	const TArray<FDebugMenuNodeDefinition>& Nodes,
	FText& OutError)
{
	if (!IsValid(Registry))
	{
		OutError = NSLOCTEXT("ReusableDebugMenu", "RegistryUnavailable", "The debug menu registry is unavailable.");
		return false;
	}

	for (const FDebugMenuNodeDefinition& Node : Nodes)
	{
		if (Node.NodeType != EDebugMenuNodeType::Category)
		{
			OutError = FText::Format(
				NSLOCTEXT(
					"ReusableDebugMenu",
					"CommandRequiresAdapter",
					"Command '{0}' requires RegisterWindowNode or a catalog adapter."),
				FText::FromName(Node.NodeId));
			return false;
		}
	}

	return Registry->RegisterNodes(Nodes, OutError);
}

bool UReusableDebugMenuSubsystem::RegisterWindowNode(
	const FDebugMenuNodeDefinition& Node,
	TSubclassOf<UReusableDebugMenuWindow> WindowClass,
	FText& OutError)
{
	if (!IsValid(Registry) || !IsValid(WindowManager))
	{
		OutError = NSLOCTEXT("ReusableDebugMenu", "RegistryUnavailable", "The debug menu registry is unavailable.");
		return false;
	}

	if (Node.NodeType != EDebugMenuNodeType::Command ||
		!WindowClass ||
		WindowClass->HasAnyClassFlags(CLASS_Abstract))
	{
		OutError = FText::Format(
			NSLOCTEXT(
				"ReusableDebugMenu",
				"InvalidWindowAdapter",
				"Command '{0}' requires a concrete debug window class."),
			FText::FromName(Node.NodeId));
		return false;
	}

	if (!Registry->RegisterNode(Node, OutError))
	{
		return false;
	}

	WindowManager->SetWindowClass(Node.NodeId, WindowClass);
	return true;
}

bool UReusableDebugMenuSubsystem::RegisterCatalog(
	const UReusableDebugMenuCatalog* Catalog,
	FText& OutError)
{
	if (!IsValid(Registry) || !IsValid(WindowManager) || !IsValid(Catalog))
	{
		OutError = NSLOCTEXT("ReusableDebugMenu", "InvalidCatalog", "The debug menu catalog or registry is invalid.");
		return false;
	}

	TArray<FDebugMenuNodeDefinition> Nodes;
	Nodes.Reserve(Catalog->Entries.Num());
	TMap<FName, TSubclassOf<UReusableDebugMenuWindow>> CandidateWindowClasses =
		WindowManager->GetWindowClasses();

	for (const FDebugMenuCatalogEntry& Entry : Catalog->Entries)
	{
		Nodes.Add(Entry.Node);

		if (Entry.Node.NodeType == EDebugMenuNodeType::Category)
		{
			if (Entry.WindowClass)
			{
				OutError = FText::Format(
					NSLOCTEXT(
						"ReusableDebugMenu",
						"CategoryHasAdapter",
						"Category '{0}' must not specify a window adapter. Clear WindowClass or change NodeType to Command."),
					FText::FromName(Entry.Node.NodeId));
				return false;
			}

			CandidateWindowClasses.Remove(Entry.Node.NodeId);
			continue;
		}

		if (!Entry.WindowClass || Entry.WindowClass->HasAnyClassFlags(CLASS_Abstract))
		{
			OutError = FText::Format(
				NSLOCTEXT(
					"ReusableDebugMenu",
					"CommandHasInvalidAdapter",
					"Command '{0}' requires a concrete debug window adapter."),
				FText::FromName(Entry.Node.NodeId));
			return false;
		}

		CandidateWindowClasses.Add(Entry.Node.NodeId, Entry.WindowClass);
	}

	if (!Registry->RegisterNodes(Nodes, OutError))
	{
		return false;
	}

	WindowManager->SetWindowClasses(MoveTemp(CandidateWindowClasses));
	return true;
}

bool UReusableDebugMenuSubsystem::ToggleMenu()
{
	if (IsMenuOpen())
	{
		HideMenu();
		return false;
	}

	return ShowMenu();
}

bool UReusableDebugMenuSubsystem::ShowMenu()
{
#if UE_BUILD_SHIPPING
	return false;
#else
	if (IsMenuOpen())
	{
		return true;
	}

	APlayerController* PlayerController = ResolvePlayerController();
	if (!IsValid(PlayerController))
	{
		UE_LOG(LogReusableDebugMenu, Warning, TEXT("Cannot open debug menu without a local PlayerController."));
		return false;
	}

	if (HasActiveDebugWindows() && GameplayState.GetPlayerController() != PlayerController)
	{
		CloseAllWindows();
		HideMenu();
	}

	if (!MenuWidgetClass || MenuWidgetClass->HasAnyClassFlags(CLASS_Abstract))
	{
		UE_LOG(
			LogReusableDebugMenu,
			Error,
			TEXT("Cannot open debug menu: MenuWidgetClass is missing or abstract."));
		return false;
	}

	if (IsValid(MenuWidget) && MenuWidget->GetOwningPlayer() != PlayerController)
	{
		MenuWidget->RemoveFromParent();
		MenuWidget = nullptr;
	}

	if (!IsValid(MenuWidget))
	{
		MenuWidget = CreateWidget<UReusableDebugMenuRootWidget>(
			PlayerController,
			MenuWidgetClass);
		if (!IsValid(MenuWidget))
		{
			UE_LOG(LogReusableDebugMenu, Error, TEXT("Failed to create debug menu root widget."));
			return false;
		}

		MenuWidget->InitializeMenu(Registry);
		MenuWidget->OnWindowRequested().BindUObject(this, &ThisClass::ToggleWindow);
		MenuWidget->OnCloseRequested().BindUObject(this, &ThisClass::HideMenu);
		MenuWidget->OnToggleInputRequested().BindUObject(this, &ThisClass::MatchesToggleInput);
	}

	if (!MenuWidget->AddToPlayerScreen(1000))
	{
		UE_LOG(LogReusableDebugMenu, Error, TEXT("Failed to add debug menu to the local player's screen."));
		return false;
	}

	const bool bDebugSessionAlreadyActive = bMenuOpen || HasActiveDebugWindows();
	if (!bDebugSessionAlreadyActive)
	{
		GameplayState.Capture(PlayerController);
	}
	else if (GameplayState.GetPlayerController() == nullptr)
	{
		GameplayState.Capture(PlayerController);
	}

	if (bPauseGameWhenOpen && PlayerController->GetWorld() && !PlayerController->GetWorld()->IsPaused())
	{
		const bool bPausedBySubsystem = PlayerController->SetPause(true);
		if (bPausedBySubsystem)
		{
			GameplayState.MarkPausedBySubsystem();
		}
		else
		{
			UE_LOG(
				LogReusableDebugMenu,
				Warning,
				TEXT("The game rejected pause; the debug menu remains available."));
		}
	}

	GameplayState.ApplyMenuInputMode(bManageInputMode, MenuWidget);

	bMenuOpen = true;
	MenuWidget->SetFocusToFirstItem();
	VisibilityChanged.Broadcast(true);
	return true;
#endif
}

void UReusableDebugMenuSubsystem::HideMenu()
{
	const bool bWasOpen = bMenuOpen || (IsValid(MenuWidget) && MenuWidget->IsInViewport());

	if (IsValid(MenuWidget))
	{
		MenuWidget->RemoveFromParent();
	}

	bMenuOpen = false;
	ReleaseMenuGameplayState();

	if (bWasOpen)
	{
		VisibilityChanged.Broadcast(false);
	}
}

void UReusableDebugMenuSubsystem::NotifyPlayerControllerEndPlay(
	const APlayerController* PlayerController)
{
	if (GameplayState.GetPlayerController() == PlayerController ||
		(IsValid(MenuWidget) && MenuWidget->GetOwningPlayer() == PlayerController))
	{
		CloseAllWindows();
		HideMenu();
		MenuWidget = nullptr;
	}
}

bool UReusableDebugMenuSubsystem::IsMenuOpen() const
{
	return bMenuOpen && IsValid(MenuWidget) && MenuWidget->IsInViewport();
}

APlayerController* UReusableDebugMenuSubsystem::ResolvePlayerController() const
{
	const ULocalPlayer* LocalPlayer = GetLocalPlayer();
	return IsValid(LocalPlayer) ? LocalPlayer->GetPlayerController(GetWorld()) : nullptr;
}

bool UReusableDebugMenuSubsystem::MatchesToggleInput(const FKeyEvent& KeyEvent) const
{
	return ToggleInputRequested.IsBound() && ToggleInputRequested.Execute(KeyEvent);
}

bool UReusableDebugMenuSubsystem::HasActiveDebugWindows() const
{
	return IsValid(WindowManager) && WindowManager->HasActiveWindows();
}

void UReusableDebugMenuSubsystem::ReleaseMenuGameplayState()
{
	GameplayState.ReleasePause();

	if (HasActiveDebugWindows())
	{
		// Debug Windowは独立したVisual Overlayです。Windowを画面に残したまま、
		// MouseとKeyboardのInputだけをGameへ戻します。
		GameplayState.RestoreInputState(bManageInputMode);
		return;
	}

	RestoreGameplayStateIfIdle();
}

void UReusableDebugMenuSubsystem::RestoreGameplayStateIfIdle()
{
	if (bMenuOpen || HasActiveDebugWindows())
	{
		return;
	}

	GameplayState.RestoreInputState(bManageInputMode);
	GameplayState.Reset();
}

void UReusableDebugMenuSubsystem::ToggleWindow(const FName NodeId)
{
	if (IsValid(WindowManager))
	{
		WindowManager->ToggleWindow(NodeId, GameplayState.GetPlayerController());
	}
}

void UReusableDebugMenuSubsystem::CloseWindow(const FName NodeId)
{
	if (IsValid(WindowManager))
	{
		WindowManager->CloseWindow(NodeId);
	}

	RestoreGameplayStateIfIdle();
}

void UReusableDebugMenuSubsystem::CloseAllWindows()
{
	if (IsValid(WindowManager))
	{
		WindowManager->CloseAllWindows();
	}
}
