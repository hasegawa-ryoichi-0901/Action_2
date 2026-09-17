#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "DebugMenuListEntryWidget.generated.h"

class UButton;
class UTextBlock;

/**
 * @brief 1つのDebug Menu Itemを表示する再利用可能なUListView Rowです。
 *
 * C++がNode Textと選択処理を提供し、BlueprintはVisual Layoutと
 * OptionalなSelector／Button Widgetだけを担当します。
 */
UCLASS(Abstract, Blueprintable)
class REUSABLEDEBUGMENU_API UReusableDebugMenuListEntryWidget
	: public UUserWidget
	, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UButton> entryButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> entryTitleText;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> selectorText;
};
