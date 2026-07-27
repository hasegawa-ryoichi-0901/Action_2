#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "../BaseCharacter.h"
#include "../../Input/Interface/IPlayerInputComponent.h"
#include "../../Input/Components/BasePlayerInputComponent.h"
#include "Components/SceneComponent.h"
#include "InputMappingContext.h"
#include "BasePlayer.generated.h"
/**
 * プレイヤーの基盤クラス。
 *
 */
UCLASS()
class ACTION_2_API ABasePlayer : public ABaseCharacter
{
	GENERATED_BODY()
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
    ABasePlayer();
protected:
	/// @brief インプットアクションを自動アサインする変数
	UPROPERTY(
    VisibleInstanceOnly,
    BlueprintReadOnly,
    Transient,
    Category = "Input")
	TMap<FGameplayTag, TScriptInterface<IPlayerInputComponent>> PlayerInputComponents;
	/// @brief 操作に使用するMappingContext
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputMappingContext* DefaultMappingContext;
protected:
// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* playerInputComponent) override;
	virtual void TeardownPlayerInputComponents();
	virtual void EnableMappingContext();
	virtual void DisableMappingContext();
	virtual void UnPossessed();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
private:
	UPROPERTY(VisibleInstanceOnly, Transient, Category = Input)
	bool bInputEnabled = true;
	UEnhancedInputLocalPlayerSubsystem* GetInputSubsystem(AController* controller);
	void ApplyInputEnabledState();
public:
	void SetInputEnabled(bool bEnabled);
};
