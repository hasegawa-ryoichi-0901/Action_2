#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "DebugMenuTypes.h"
#include "DebugMenuGameplayState.h"
#include "DebugMenuSubsystem.generated.h"

class APlayerController;
class UReusableDebugMenuCatalog;
class UReusableDebugMenuRegistry;
class UReusableDebugMenuRootWidget;
class UReusableDebugMenuWindow;
class UReusableDebugMenuWindowManager;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnDebugMenuVisibilityChanged, bool);

/**
 * @brief LocalPlayer単位のDebug Menuユースケースを提供するApplication Facadeです。
 *
 * MenuのLifecycle、Registry／Catalog登録、Gameplay Stateの復元、
 * WindowManager操作を調整します。PlayerControllerのInput Bindingは所有せず、
 * UReusableDebugMenuControllerComponentが担当します。
 */
UCLASS()
class REUSABLEDEBUGMENU_API UReusableDebugMenuSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	void Configure(
		TSubclassOf<UReusableDebugMenuRootWidget> InMenuWidgetClass,
		const UReusableDebugMenuCatalog* InCatalog = nullptr,
		bool bInPauseGameWhenOpen = true,
		bool bInManageInputMode = true);

	bool RegisterNode(const FDebugMenuNodeDefinition& Node, FText& OutError);
	bool RegisterNodes(const TArray<FDebugMenuNodeDefinition>& Nodes, FText& OutError);
	bool RegisterWindowNode(
		const FDebugMenuNodeDefinition& Node,
		TSubclassOf<UReusableDebugMenuWindow> WindowClass,
		FText& OutError);
	bool RegisterCatalog(const UReusableDebugMenuCatalog* Catalog, FText& OutError);

	bool ToggleMenu();
	bool ShowMenu();
	/** Root Menuだけを隠し、表示中のDebug Windowは残したままゲームを継続します。 */
	void HideMenu();
	void NotifyPlayerControllerEndPlay(const APlayerController* PlayerController);
	/** Root Menuの表示状態を返します。独立したDebug Windowは表示中の可能性があります。 */
	bool IsMenuOpen() const;

	UReusableDebugMenuRegistry* GetRegistry() const { return Registry; }
	FOnDebugMenuVisibilityChanged& OnVisibilityChanged() { return VisibilityChanged; }
	FDebugMenuToggleInputMatcher& OnToggleInputRequested() { return ToggleInputRequested; }

private:
	APlayerController* ResolvePlayerController() const;
	bool MatchesToggleInput(const FKeyEvent& KeyEvent) const;
	bool HasActiveDebugWindows() const;
	void ReleaseMenuGameplayState();
	void RestoreGameplayStateIfIdle();
	void ToggleWindow(FName NodeId);
	void CloseWindow(FName NodeId);
	void CloseAllWindows();

	UPROPERTY(Transient)
	TObjectPtr<UReusableDebugMenuRegistry> Registry;

	UPROPERTY(Transient)
	TObjectPtr<UReusableDebugMenuWindowManager> WindowManager;

	UPROPERTY(Transient)
	TObjectPtr<UReusableDebugMenuRootWidget> MenuWidget;

	UPROPERTY(Transient)
	TSubclassOf<UReusableDebugMenuRootWidget> MenuWidgetClass;

	bool bMenuOpen = false;
	bool bPauseGameWhenOpen = true;
	bool bManageInputMode = true;
	FReusableDebugMenuGameplayState GameplayState;
	FOnDebugMenuVisibilityChanged VisibilityChanged;
	FDebugMenuToggleInputMatcher ToggleInputRequested;
};
