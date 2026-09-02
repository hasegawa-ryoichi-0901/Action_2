#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ActionPlayerController.generated.h"

class UEnhancedInputComponent;
class UInputAction;
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
	void ConfigureDebugMenu();
	void RegisterFallbackDebugCategories(UReusableDebugMenuSubsystem& Subsystem);
	void RemoveDebugMenuInputBinding();
	UReusableDebugMenuSubsystem* GetDebugMenuSubsystem() const;

	TWeakObjectPtr<UEnhancedInputComponent> BoundDebugInputComponent;
	uint32 DebugMenuBindingHandle = 0;
};
