#include "Window/ReusableDebugMenuWindowManager.h"

#include "DebugMenuRegistry.h"
#include "ReusableDebugMenu.h"
#include "UI/DebugMenuWindow.h"

void UReusableDebugMenuWindowManager::Initialize(
	UReusableDebugMenuRegistry* InRegistry)
{
	Registry = InRegistry;
}

void UReusableDebugMenuWindowManager::SetWindowClass(
	const FName NodeId,
	TSubclassOf<UReusableDebugMenuWindow> WindowClass)
{
	if (!NodeId.IsNone() && WindowClass)
	{
		WindowClasses.Add(NodeId, WindowClass);
	}
}

void UReusableDebugMenuWindowManager::SetWindowClasses(
	TMap<FName, TSubclassOf<UReusableDebugMenuWindow>> InWindowClasses)
{
	WindowClasses = MoveTemp(InWindowClasses);
}

void UReusableDebugMenuWindowManager::ToggleWindow(
	const FName NodeId,
	APlayerController* PlayerController)
{
	if (TObjectPtr<UReusableDebugMenuWindow>* Existing = ActiveWindows.Find(NodeId))
	{
		if (IsValid(*Existing) && (*Existing)->IsInViewport())
		{
			CloseWindow(NodeId);
			return;
		}

		ActiveWindows.Remove(NodeId);
	}

	if (!IsValid(Registry) || !IsValid(PlayerController))
	{
		return;
	}

	const FDebugMenuNodeDefinition* Node = Registry->FindNode(NodeId);
	const TSubclassOf<UReusableDebugMenuWindow>* WindowClass = WindowClasses.Find(NodeId);
	if (Node == nullptr ||
		Node->NodeType != EDebugMenuNodeType::Command ||
		WindowClass == nullptr ||
		!*WindowClass)
	{
		UE_LOG(
			LogReusableDebugMenu,
			Warning,
			TEXT("Cannot open unregistered or invalid debug window '%s'."),
			*NodeId.ToString());
		return;
	}

	UReusableDebugMenuWindow* Window = CreateWidget<UReusableDebugMenuWindow>(
		PlayerController,
		*WindowClass);
	if (!IsValid(Window))
	{
		UE_LOG(
			LogReusableDebugMenu,
			Error,
			TEXT("Failed to create debug window '%s'."),
			*NodeId.ToString());
		return;
	}

	Window->InitializeDebugWindow(NodeId);
	Window->OnCloseRequested().BindUObject(
		this,
		&ThisClass::CloseWindow);
	if (!Window->AddToPlayerScreen(1001))
	{
		return;
	}

	ActiveWindows.Add(NodeId, Window);
	Window->NotifyOpened();
}

void UReusableDebugMenuWindowManager::CloseWindow(const FName NodeId)
{
	TObjectPtr<UReusableDebugMenuWindow> Window;
	if (!ActiveWindows.RemoveAndCopyValue(NodeId, Window))
	{
		return;
	}

	if (IsValid(Window))
	{
		Window->NotifyClosed();
		Window->RemoveFromParent();
	}
}

void UReusableDebugMenuWindowManager::CloseAllWindows()
{
	TArray<FName> WindowIds;
	ActiveWindows.GetKeys(WindowIds);
	for (const FName WindowId : WindowIds)
	{
		CloseWindow(WindowId);
	}
}

bool UReusableDebugMenuWindowManager::HasActiveWindows() const
{
	for (const TPair<FName, TObjectPtr<UReusableDebugMenuWindow>>& Pair : ActiveWindows)
	{
		if (IsValid(Pair.Value) && Pair.Value->IsInViewport())
		{
			return true;
		}
	}

	return false;
}
