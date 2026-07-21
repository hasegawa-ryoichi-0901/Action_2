// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Interface/IPlayerInputComponent.h"
#include "BasePlayerInputComponent.generated.h"


UCLASS(
    Abstract,
	BlueprintType,
    Blueprintable,
    ClassGroup = "Input",
    meta = (BlueprintSpawnableComponent)
)
class ACTION_2_API UBasePlayerInputComponent
	: public UActorComponent
	, public IPlayerInputComponent
{
	GENERATED_BODY()
public:
	// Sets default values for this component's properties
	//UBasePlayerInputComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    FTaggedInputAction TaggedInputAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	bool bIsPressed = false;
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual const FTaggedInputAction& GetTaggedInputAction() const override
    {
        return TaggedInputAction;
    }

	virtual const bool& IsPressed() const override
	{
		return bIsPressed;
	}
	virtual void Setup(UInputComponent* InputComponent) override;
	/* キーを押下した際の制御 */
	virtual void HandlePressedAction() override;
	/* キーを離した際の制御 */
	virtual void HandleReleasedAction() override;
	/*Input有効化*/
	virtual  void Enable(APlayerController& controller) override;
	/*Input無効化*/
	virtual  void Disable(APlayerController& controller) override;


};
