#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DebugMenuWindow.generated.h"

DECLARE_DELEGATE_OneParam(FOnDebugMenuWindowCloseRequested, FName);

/**
 * @brief プロジェクト固有のCommand UIを実装するBlueprint向け基底Widgetです。
 *
 * 生成と破棄はWindowManagerが所有します。派生WidgetはCommand UIを提供し、
 * 自身をViewportから直接削除せずRequestCloseで終了要求を発行します。
 */
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
