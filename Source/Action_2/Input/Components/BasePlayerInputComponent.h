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

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    FTaggedInputAction TaggedInputAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	bool bIsPressed = false;
	public:
	// Called every frame

	virtual const FTaggedInputAction& GetTaggedInputAction() const override
    {
		return TaggedInputAction;
    }

	virtual bool IsPressed() const override
	{
		return bIsPressed;
	}
	virtual void Setup(UInputComponent& InputComponent) final override;
	virtual void Teardown() final override;
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void BindActions(
		UEnhancedInputComponent& InputComponent,
		const UInputAction& InputAction
    );
private:
    TWeakObjectPtr<UEnhancedInputComponent>
        BoundInputComponent;
};
