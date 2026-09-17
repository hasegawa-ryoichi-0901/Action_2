#include "UI/DebugMenuListEntryWidget.h"

#include "Components/TextBlock.h"
#include "UI/DebugMenuListItemObject.h"

void UReusableDebugMenuListEntryWidget::NativeOnListItemObjectSet(
	UObject* ListItemObject)
{
	const UDebugMenuListItemObject* Item = Cast<UDebugMenuListItemObject>(ListItemObject);
	if (!ensureMsgf(IsValid(Item), TEXT("Debug menu ListView received an unsupported item object.")) ||
		!ensureMsgf(IsValid(entryTitleText), TEXT("Debug menu entry requires a widget named 'entryTitleText'.")))
	{
		return;
	}

	entryTitleText->SetText(Item->GetDefinition().DisplayName);
	if (IsValid(selectorText))
	{
		selectorText->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UReusableDebugMenuListEntryWidget::NativeOnItemSelectionChanged(
	const bool bIsSelected)
{
	if (IsValid(selectorText))
	{
		selectorText->SetVisibility(
			bIsSelected ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Hidden);
	}
}
