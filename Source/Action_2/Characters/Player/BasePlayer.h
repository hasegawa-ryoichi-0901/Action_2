#pragma once

#include "CoreMinimal.h"
#include "../BaseCharacter.h"
#include "../../Input/Interface/IPlayerInputComponent.h"
#include "../../Input/Components/BasePlayerInputComponent.h"
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
protected:
	UPROPERTY(
    VisibleInstanceOnly,
    BlueprintReadOnly,
    Transient,
    Category = "Input")
	TArray<TScriptInterface<IPlayerInputComponent>> PlayerInputComponents;
	/** MappingContext */
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
