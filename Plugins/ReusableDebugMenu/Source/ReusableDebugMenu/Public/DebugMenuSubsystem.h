#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "DebugMenuTypes.h"
#include "DebugMenuSubsystem.generated.h"

class APlayerController;
class UReusableDebugMenuCatalog;
class UReusableDebugMenuRegistry;
class UReusableDebugMenuRootWidget;
class UReusableDebugMenuWindow;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnDebugMenuVisibilityChanged, bool);

/**
 * Application facade for menu lifecycle and window use cases.
 * Local-player scope avoids Player Index 0 assumptions and split-screen leaks.
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
	/** Hides only the root menu; active debug windows remain visible and the game continues. */
	void HideMenu();
	void NotifyPlayerControllerEndPlay(const APlayerController* PlayerController);
	/** Returns whether the root menu is visible; independent windows may still be open. */
	bool IsMenuOpen() const;

	UReusableDebugMenuRegistry* GetRegistry() const { return Registry; }
	FOnDebugMenuVisibilityChanged& OnVisibilityChanged() { return VisibilityChanged; }

private:
	APlayerController* ResolvePlayerController() const;
	bool HasActiveDebugWindows() const;
	void RestoreGameplayInputState();
	void ReleaseMenuGameplayState();
	void RestoreGameplayStateIfIdle();
	void ToggleWindow(FName NodeId);
	void CloseWindow(FName NodeId);
	void CloseAllWindows();

	UPROPERTY(Transient)
	TObjectPtr<UReusableDebugMenuRegistry> Registry;

	UPROPERTY(Transient)
	TObjectPtr<UReusableDebugMenuRootWidget> MenuWidget;

	UPROPERTY(Transient)
	TMap<FName, TObjectPtr<UReusableDebugMenuWindow>> ActiveWindows;

	UPROPERTY(Transient)
	TMap<FName, TSubclassOf<UReusableDebugMenuWindow>> WindowClasses;

	UPROPERTY(Transient)
	TWeakObjectPtr<APlayerController> MenuOwnerController;

	UPROPERTY(Transient)
	TSubclassOf<UReusableDebugMenuRootWidget> MenuWidgetClass;

	bool bMenuOpen = false;
	bool bPauseGameWhenOpen = true;
	bool bManageInputMode = true;
	bool bPausedBySubsystem = false;
	bool bPreviousMouseCursorVisible = false;
	FOnDebugMenuVisibilityChanged VisibilityChanged;
};
