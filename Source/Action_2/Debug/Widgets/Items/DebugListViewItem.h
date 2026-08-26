// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Components/Button.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "DebugListViewItem.generated.h"

/**
 *
 */
UCLASS()
class ACTION_2_API UDebugListViewItem : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
public:
	void Setup();
protected:
	// IUserObjectListEntry のオーバーライド
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	virtual void NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent) override;
	virtual void NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent) override;
	virtual FReply NativeOnPreviewKeyDown(
		const FGeometry& InGeometry,
		const FKeyEvent& InKeyEvent) override;
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> entryButton;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> entryTitleText;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> selectorText;
private:
	//UPROPERTY(meta = (BindWidget))
	TObjectPtr<UListView> debugListView;
	void ConfirmSelectedItem();
};
