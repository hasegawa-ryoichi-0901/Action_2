#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DebugMenuWindow.generated.h"

DECLARE_DELEGATE_OneParam(FOnDebugMenuWindowCloseRequested, FName);

/** Project-specific debug windows derive from this presentation port. */
UCLASS(Abstract, Blueprintable)
class REUSABLEDEBUGMENU_API UReusableDebugMenuWindow : public UUserWidget
{
	GENERATED_BODY()

public:
	FName GetNodeId() const { return NodeId; }

	UFUNCTION(BlueprintCallable, Category = "Debug Menu")
	void RequestClose();

	void InitializeDebugWindow(FName InNodeId);
	void NotifyOpened();
	void NotifyClosed();
	FOnDebugMenuWindowCloseRequested& OnCloseRequested() { return CloseRequested; }

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Debug Menu", meta = (DisplayName = "On Debug Window Opened"))
	void ReceiveDebugWindowOpened();

	UFUNCTION(BlueprintImplementableEvent, Category = "Debug Menu", meta = (DisplayName = "On Debug Window Closed"))
	void ReceiveDebugWindowClosed();

private:
	UPROPERTY(Transient)
	FName NodeId = NAME_None;

	bool bOpened = false;
	FOnDebugMenuWindowCloseRequested CloseRequested;
};
