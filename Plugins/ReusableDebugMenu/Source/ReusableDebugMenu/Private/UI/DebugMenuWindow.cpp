#include "UI/DebugMenuWindow.h"

void UReusableDebugMenuWindow::InitializeDebugWindow(const FName InNodeId)
{
	NodeId = InNodeId;

	// Debug windows are interactive overlays managed by the subsystem. Enforce
	// focus support in C++ so each host project's Widget Blueprint does not need
	// to repeat the same Class Defaults setting.
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
