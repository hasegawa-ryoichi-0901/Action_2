#include "UI/DebugMenuRootWidget.h"

#include "Components/ListView.h"
#include "DebugMenuRegistry.h"
#include "InputCoreTypes.h"
#include "UI/DebugMenuListItemObject.h"

void UReusableDebugMenuRootWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (!ensureMsgf(IsValid(debugListView), TEXT("Debug menu root requires a ListView named 'debugListView'.")))
	{
		return;
	}

	debugListView->OnItemDoubleClicked().AddUObject(
		this,
		&ThisClass::HandleItemDoubleClicked);
	RebuildVisibleItems();
}

void UReusableDebugMenuRootWidget::InitializeMenu(
	UReusableDebugMenuRegistry* InRegistry)
{
	if (Registry == InRegistry)
	{
		RebuildVisibleItems();
		return;
	}

	if (IsValid(Registry) && RegistryChangedHandle.IsValid())
	{
		Registry->OnChanged().Remove(RegistryChangedHandle);
	}

	Registry = InRegistry;
	RegistryChangedHandle.Reset();
	CurrentParentId = NAME_None;
	NavigationStack.Reset();

	if (IsValid(Registry))
	{
		RegistryChangedHandle = Registry->OnChanged().AddUObject(
			this,
			&ThisClass::RebuildVisibleItems);
	}

	RebuildVisibleItems();
}

void UReusableDebugMenuRootWidget::SetFocusToFirstItem()
{
	if (!IsValid(debugListView) || debugListView->GetNumItems() == 0)
	{
		return;
	}

	debugListView->SetSelectedIndex(0);
	debugListView->NavigateToIndex(0);
	debugListView->SetKeyboardFocus();
}

FReply UReusableDebugMenuRootWidget::NativeOnPreviewKeyDown(
	const FGeometry& InGeometry,
	const FKeyEvent& InKeyEvent)
{
	const FKey Key = InKeyEvent.GetKey();
	if (Key == EKeys::Enter || Key == EKeys::Gamepad_FaceButton_Bottom)
	{
		ConfirmSelectedItem();
		return FReply::Handled();
	}

	if (Key == EKeys::Escape || Key == EKeys::BackSpace || Key == EKeys::Gamepad_FaceButton_Right)
	{
		NavigateBackOrClose();
		return FReply::Handled();
	}

	return Super::NativeOnPreviewKeyDown(InGeometry, InKeyEvent);
}

void UReusableDebugMenuRootWidget::RebuildVisibleItems()
{
	if (!IsValid(debugListView))
	{
		return;
	}

	VisibleItems.Reset();
	debugListView->ClearListItems();

	if (!IsValid(Registry))
	{
		return;
	}

	if (!CurrentParentId.IsNone() && !Registry->Contains(CurrentParentId))
	{
		CurrentParentId = NAME_None;
		NavigationStack.Reset();
	}

	const TArray<FDebugMenuNodeDefinition> Children = Registry->GetChildren(CurrentParentId);
	VisibleItems.Reserve(Children.Num());
	for (const FDebugMenuNodeDefinition& Definition : Children)
	{
		UDebugMenuListItemObject* Item = NewObject<UDebugMenuListItemObject>(this);
		Item->Initialize(Definition);
		VisibleItems.Add(Item);
		debugListView->AddItem(Item);
	}

	SetFocusToFirstItem();
}

void UReusableDebugMenuRootWidget::ConfirmSelectedItem()
{
	if (!IsValid(debugListView))
	{
		return;
	}

	const UDebugMenuListItemObject* Item =
		debugListView->GetSelectedItem<UDebugMenuListItemObject>();
	if (!IsValid(Item))
	{
		return;
	}

	const FDebugMenuNodeDefinition& Definition = Item->GetDefinition();
	if (Definition.NodeType == EDebugMenuNodeType::Category)
	{
		NavigationStack.Add(CurrentParentId);
		CurrentParentId = Definition.NodeId;
		RebuildVisibleItems();
		return;
	}

	// The application layer decides which adapter executes this command.
	WindowRequested.ExecuteIfBound(Definition.NodeId);
}

void UReusableDebugMenuRootWidget::NavigateBackOrClose()
{
	if (NavigationStack.IsEmpty())
	{
		CloseRequested.ExecuteIfBound();
		return;
	}

	CurrentParentId = NavigationStack.Pop(EAllowShrinking::No);
	RebuildVisibleItems();
}

void UReusableDebugMenuRootWidget::HandleItemDoubleClicked(UObject* Item)
{
	if (IsValid(debugListView) && IsValid(Item))
	{
		debugListView->SetSelectedItem(Item);
		ConfirmSelectedItem();
	}
}
