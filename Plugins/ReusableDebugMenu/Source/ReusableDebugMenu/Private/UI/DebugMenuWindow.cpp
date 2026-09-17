#include "UI/DebugMenuWindow.h"

void UReusableDebugMenuWindow::InitializeDebugWindow(const FName InNodeId)
{
	NodeId = InNodeId;

	// Debug WindowはSubsystemが管理するInteractive Overlayです。各Host Projectの
	// Widget Blueprintで同じClass Defaults設定を繰り返さなくて済むよう、
	// C++側でFocus対応を強制します。
	SetIsFocusable(true);
}

void UReusableDebugMenuWindow::NotifyOpened()
{
	if (!bOpened)
	{
		bOpened = true;
		ReceiveDebugWindowOpened();
	}
}

void UReusableDebugMenuWindow::NotifyClosed()
{
	if (bOpened)
	{
		bOpened = false;
		ReceiveDebugWindowClosed();
	}
}

void UReusableDebugMenuWindow::RequestClose()
{
	if (!NodeId.IsNone())
	{
		CloseRequested.ExecuteIfBound(NodeId);
	}
}
