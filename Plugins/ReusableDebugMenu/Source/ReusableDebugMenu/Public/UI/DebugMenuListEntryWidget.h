#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "DebugMenuListEntryWidget.generated.h"

class UButton;
class UTextBlock;

/** Generic UListView row. Blueprint is responsible only for visual layout. */
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
