// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ListView.h"
#include "../Debug/Widgets/Items/DebugListViewItem.h"
#include "DebugRootWidget.generated.h"

/**
 *
 */
UCLASS(Abstract)
class ACTION_2_API UDebugRootWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;
	virtual FReply NativeOnPreviewKeyDown(
		const FGeometry& InGeometry,
		const FKeyEvent& InKeyEvent) override;
public:
	void SetFocusToFirstItem();

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UListView> debugListView;
private:
	void ConfirmSelectedItem();
};
