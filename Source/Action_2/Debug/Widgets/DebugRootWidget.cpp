// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widgets/DebugRootWidget.h"
#include "Blueprint/UserWidget.h"
#include "../Debug/Widgets/Items/DebugListViewItem.h"
#include "../EDebugMenuCategory.h"

void UDebugRootWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	for (const EDebugMenuCategory Category : TEnumRange<EDebugMenuCategory>())
	{
		UDebugListViewItem* item = NewObject<UDebugListViewItem>(this);
		this->debugListView->AddItem(item);
	}
	this->SetFocusToFirstItem();
}

void UDebugRootWidget::SetFocusToFirstItem()
{
	if (!IsValid(debugListView) || debugListView->GetNumItems() == 0)
	{
		return;
	}
	debugListView->SetSelectedIndex(0);
	debugListView->NavigateToIndex(0);
}

FReply UDebugRootWidget::NativeOnPreviewKeyDown(
	const FGeometry& InGeometry,
	const FKeyEvent& InKeyEvent)
{
	const FKey Key = InKeyEvent.GetKey();
	if (Key == EKeys::Enter)
	{
		this->ConfirmSelectedItem();
	}
	return Super::NativeOnPreviewKeyDown(
		InGeometry,
		InKeyEvent);
}

void UDebugRootWidget::ConfirmSelectedItem()
{
	if (!IsValid(debugListView))
	{
		return;
	}

	UObject* SelectedItem = debugListView->GetSelectedItem();
	if (!IsValid(SelectedItem))
	{
		return;
	}
	UDebugListViewItem* debugListViewItem = Cast<UDebugListViewItem>(SelectedItem);
	if(!IsValid(debugListViewItem)){
		return;
	}
	// 選択項目に対応する決定処理
	UE_LOG(
		LogTemp,
		Log,
		TEXT("Confirmed: %s"),
		*SelectedItem->GetName());

	// ListのWidget生成する
	// ListViewのクラスでItemをEnum分生成する

}
