#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ReusableDebugMenuWindowManager.generated.h"

class APlayerController;
class UReusableDebugMenuRegistry;
class UReusableDebugMenuWindow;

/**
 * @brief Debug Window Widgetの対応付けとRuntime Lifetimeを所有します。
 *
 * Registryを通じてCommand Nodeを解決し、対応するUMG Windowを生成・終了し、
 * Open／CloseのLifecycle Callbackを発行します。Gameplay Pause、Input Mode、
 * PlayerController Bindingはこのクラスの責務外です。
 */
UCLASS()
class UReusableDebugMenuWindowManager : public UObject
{
	GENERATED_BODY()

public:
	void Initialize(UReusableDebugMenuRegistry* InRegistry);

	void SetWindowClass(
		FName NodeId,
		TSubclassOf<UReusableDebugMenuWindow> WindowClass);
	void SetWindowClasses(
		TMap<FName, TSubclassOf<UReusableDebugMenuWindow>> InWindowClasses);

	const TMap<FName, TSubclassOf<UReusableDebugMenuWindow>>& GetWindowClasses() const
	{
		return WindowClasses;
	}

	void ToggleWindow(FName NodeId, APlayerController* PlayerController);
	void CloseWindow(FName NodeId);
	void CloseAllWindows();
	bool HasActiveWindows() const;

private:
	UPROPERTY(Transient)
	TObjectPtr<UReusableDebugMenuRegistry> Registry;

	UPROPERTY(Transient)
	TMap<FName, TSubclassOf<UReusableDebugMenuWindow>> WindowClasses;

	UPROPERTY(Transient)
	TMap<FName, TObjectPtr<UReusableDebugMenuWindow>> ActiveWindows;
};
