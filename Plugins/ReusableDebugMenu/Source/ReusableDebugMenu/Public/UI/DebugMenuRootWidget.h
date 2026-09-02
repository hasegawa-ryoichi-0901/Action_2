#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DebugMenuRootWidget.generated.h"

class UDebugMenuListItemObject;
class UListView;
class UReusableDebugMenuRegistry;

DECLARE_DELEGATE_OneParam(FOnDebugMenuWindowRequested, FName);
DECLARE_DELEGATE(FOnDebugMenuCloseRequested);

/**
 * Generic tree navigation view. It knows how to navigate definitions, but does
 * not know how windows are created or what game systems they inspect.
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

protected:
	virtual void NativeOnInitialized() override;
	virtual FReply NativeOnPreviewKeyDown(
		const FGeometry& InGeometry,
		const FKeyEvent& InKeyEvent) override;

private:
	void RebuildVisibleItems();
	void ConfirmSelectedItem();
	void NavigateBackOrClose();
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
};
