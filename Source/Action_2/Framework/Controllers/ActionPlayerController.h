#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ActionPlayerController.generated.h"

class UEnhancedInputComponent;
class UEnhancedInputLocalPlayerSubsystem;
struct FKeyEvent;
class UInputAction;
class UInputMappingContext;
class UReusableDebugMenuCatalog;
class UReusableDebugMenuSubsystem;
class UReusableDebugMenuRootWidget;

/** Project input adapter for the reusable debug menu. */
UCLASS()
class ACTION_2_API AActionPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Debug",
		meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> toggleDebugMenuAction;

	/** Debug mapping context registered by this controller so the menu works without a Pawn. */
	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Debug",
		meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> debugInputMappingContext;

	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Debug",
		meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UReusableDebugMenuRootWidget> debugWidgetClass;

	/** Optional project data. The fallback only supplies the six design categories. */
	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category = "Debug",
		meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UReusableDebugMenuCatalog> debugMenuCatalog;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Debug")
	bool bPauseGameWhenDebugMenuOpen = true;

	/** Disable this when another project owns its own input-mode stack. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Debug")
	bool bManageDebugMenuInputMode = true;

private:
	void ToggleDebugMenu();
	bool MatchesDebugMenuToggleInput(const FKeyEvent& KeyEvent) const;
	void ConfigureDebugMenu();
	void RegisterFallbackDebugCategories(UReusableDebugMenuSubsystem& Subsystem);
	void RegisterDebugInputMappingContext();
	void RemoveDebugInputMappingContext();
	void RemoveDebugMenuInputBinding();
	UEnhancedInputLocalPlayerSubsystem* GetEnhancedInputSubsystem() const;
	UReusableDebugMenuSubsystem* GetDebugMenuSubsystem() const;

	TWeakObjectPtr<UEnhancedInputComponent> BoundDebugInputComponent;
	uint32 DebugMenuBindingHandle = 0;
	bool bDebugInputMappingContextRegistered = false;
};
