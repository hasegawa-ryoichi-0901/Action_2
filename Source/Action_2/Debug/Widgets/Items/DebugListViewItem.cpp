// Fill out your copyright notice in the Description page of Project Settings.

#include "../Items/DebugListViewItem.h"
#include "Blueprint/IUserObjectListEntry.h"

void UDebugListViewItem::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UDebugListViewItem* item = Cast<UDebugListViewItem>(ListItemObject);
	entryTitleText->SetText(FText::FromString(item->GetName()));
	selectorText->SetVisibility(ESlateVisibility::Hidden);
}

void UDebugListViewItem::NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnAddedToFocusPath(InFocusEvent);
	selectorText->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UDebugListViewItem::NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnRemovedFromFocusPath(InFocusEvent);
	selectorText->SetVisibility(ESlateVisibility::Hidden);
}

FReply UDebugListViewItem::NativeOnPreviewKeyDown(
	const FGeometry& InGeometry,
	const FKeyEvent& InKeyEvent)
{
	const FKey Key = InKeyEvent.GetKey();
	if (Key == EKeys::Enter)
	{
		//Sthis->ConfirmSelectedItem();
	}
	return Super::NativeOnPreviewKeyDown(
		InGeometry,
		InKeyEvent);
}

void UDebugListViewItem::ConfirmSelectedItem()
{
	if (!IsValid(this->debugListView))
	{
		return;
	}

	UObject* SelectedItem = debugListView->GetSelectedItem();
	if (!IsValid(SelectedItem))
	{
		return;
	}

	// 選択項目に対応する決定処理
	UE_LOG(
		LogTemp,
		Log,
		TEXT("Confirmed: %s"),
		*SelectedItem->GetName());
}

