#include "UI/DebugMenuWindow.h"

void UReusableDebugMenuWindow::InitializeDebugWindow(const FName InNodeId)
{
	NodeId = InNodeId;
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
