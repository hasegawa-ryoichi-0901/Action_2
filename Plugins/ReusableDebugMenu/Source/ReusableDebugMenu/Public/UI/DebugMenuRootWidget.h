#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DebugMenuTypes.h"
#include "DebugMenuRootWidget.generated.h"

class UDebugMenuListItemObject;
class UListView;
class UReusableDebugMenuRegistry;

DECLARE_DELEGATE_OneParam(FOnDebugMenuWindowRequested, FName);
DECLARE_DELEGATE(FOnDebugMenuCloseRequested);

/**
 * @brief RegistryのCategory／Command Treeを操作するRoot UMG Viewです。
 *
 * 表示中のItemとNavigation Inputを管理し、CloseまたはCommand実行の
 * Requestを発行します。Windowの生成やGame Systemの直接参照は行いません。
 */
UCLASS(Abstract, Blueprintable)
class REUSABLEDEBUGMENU_API UReusableDebugMenuRootWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitializeMenu(UReusableDebugMenuRegistry* InRegistry);
	void SetFocusToFirstItem();

	FOnDebugMenuWindowRequested& OnWindowRequested() { return WindowRequested; }
	FOnDebugMenuCloseRequested& OnCloseRequested() { return CloseRequested; }
	FDebugMenuToggleInputMatcher& OnToggleInputRequested() { return ToggleInputRequested; }

protected:
	virtual void NativeOnInitialized() override;
	virtual FReply NativeOnPreviewKeyDown(
		const FGeometry& InGeometry,
		const FKeyEvent& InKeyEvent) override;

private:
	void RebuildVisibleItems();
	void ConfirmSelectedItem();
	void NavigateBack();
	void HandleItemDoubleClicked(UObject* Item);

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UListView> debugListView;

	UPROPERTY(Transient)
	TObjectPtr<UReusableDebugMenuRegistry> Registry;

	UPROPERTY(Transient)
	TArray<TObjectPtr<UDebugMenuListItemObject>> VisibleItems;

	FName CurrentParentId = NAME_None;
	TArray<FName> NavigationStack;
	FDelegateHandle RegistryChangedHandle;
	FOnDebugMenuWindowRequested WindowRequested;
	FOnDebugMenuCloseRequested CloseRequested;
	FDebugMenuToggleInputMatcher ToggleInputRequested;
};
