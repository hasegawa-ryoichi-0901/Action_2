#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ReusableDebugMenuControllerComponent.generated.h"

class UEnhancedInputComponent;
class UEnhancedInputLocalPlayerSubsystem;
class UInputAction;
class UInputMappingContext;
class UReusableDebugMenuCatalog;
class UReusableDebugMenuRootWidget;
class UReusableDebugMenuSubsystem;
struct FKeyEvent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnReusableDebugMenuVisibilityChanged,
	bool,
	bIsMenuOpen);

/**
 * @brief PlayerControllerとReusableDebugMenuを接続するIntegration Adapterです。
 *
 * Enhanced Inputの登録、PlayerController／LocalPlayerの解決、Blueprint向けの
 * Convenience Callを担当します。Menu、Window、Gameplay Stateの所有は
 * UReusableDebugMenuSubsystemに委譲します。
 */
UCLASS(
	ClassGroup = (Debug),
	meta = (BlueprintSpawnableComponent))
class REUSABLEDEBUGMENU_API UReusableDebugMenuControllerComponent
	: public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Debug Menu")
	bool InitializeDebugMenu();

	UFUNCTION(BlueprintCallable, Category = "Debug Menu")
	void ToggleDebugMenu();

	UFUNCTION(BlueprintCallable, Category = "Debug Menu")
	void ShowDebugMenu();

	UFUNCTION(BlueprintCallable, Category = "Debug Menu")
	void HideDebugMenu();

	UFUNCTION(BlueprintPure, Category = "Debug Menu")
	bool IsDebugMenuOpen() const;

	UPROPERTY(BlueprintAssignable, Category = "Debug Menu")
	FOnReusableDebugMenuVisibilityChanged OnMenuVisibilityChanged;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Debug Menu|Input",
		meta = (
			AllowPrivateAccess = "true",
			ToolTip = "デバッグメニューを開閉するEnhanced Input Actionです。Startedイベントで処理します。"))
	TObjectPtr<UInputAction> ToggleMenuAction;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Debug Menu|Input",
		meta = (
		AllowPrivateAccess = "true",
		ToolTip = "Pawnの所有状態に依存せず入力を受け取るため、Local Playerへ登録するMapping Contextです。"))
	TObjectPtr<UInputMappingContext> DebugInputMappingContext;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Debug Menu",
		meta = (
		AllowPrivateAccess = "true",
		ToolTip = "UReusableDebugMenuRootWidgetを継承した具象Widget Blueprintです。debugListViewというListViewが必要です。"))
	TSubclassOf<UReusableDebugMenuRootWidget> MenuWidgetClass;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Debug Menu",
		meta = (
		AllowPrivateAccess = "true",
		ToolTip = "メニュー階層とCommandを定義するCatalogです。Commandには具象Window Blueprintを指定します。"))
	TObjectPtr<UReusableDebugMenuCatalog> Catalog;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Debug Menu",
		meta = (
			ClampMin = "0",
			ToolTip = "Debug Input Mapping Contextを登録する優先度です。通常のゲーム入力より高い値を指定します。"))
	int32 MappingContextPriority = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Debug Menu")
	bool bAutoInitialize = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Debug Menu")
	bool bPauseGameWhenOpen = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Debug Menu")
	bool bManageInputMode = true;

private:
	bool BindInput();
	void UnbindInput();
	bool RegisterMappingContext();
	void RemoveMappingContext();
	void HandleVisibilityChanged(bool bIsMenuOpen);

	bool MatchesToggleInput(const FKeyEvent& KeyEvent) const;
	APlayerController* GetOwnerPlayerController() const;
	UEnhancedInputLocalPlayerSubsystem* GetEnhancedInputSubsystem() const;
	UReusableDebugMenuSubsystem* GetDebugMenuSubsystem() const;

	TWeakObjectPtr<UEnhancedInputComponent> BoundInputComponent;
	FDelegateHandle VisibilityChangedHandle;
	uint32 InputBindingHandle = 0;
	bool bMappingContextRegistered = false;
	bool bInitialized = false;
};
