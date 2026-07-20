#pragma once

#include "CoreMinimal.h"
#include "../BaseCharacter.h"
#include "../../Input/Interface/IPlayerInputComponent.h"
#include "../../Input/Components/BasePlayerInputComponent.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TArray<TScriptInterface<IPlayerInputComponent>> PlayerInputComponents;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
