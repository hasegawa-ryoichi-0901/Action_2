// Fill out your copyright notice in the Description page of Project Settings.


#include "../Components/BasePlayerInputComponent.h"

// Sets default values for this component's properties
// UBasePlayerInputComponent::UBasePlayerInputComponent()
// {
// 	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
// 	// off to improve performance if you don't need them.
// 	PrimaryComponentTick.bCanEverTick = true;

// 	// ...
// }


// Called when the game starts
void UBasePlayerInputComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBasePlayerInputComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBasePlayerInputComponent::Setup(UInputComponent& InputComponent)
{
	Teardown();
	// 検証処理...

    UEnhancedInputComponent* EnhancedInputComponent =
        Cast<UEnhancedInputComponent>(&InputComponent);

    const UInputAction* InputAction =
        TaggedInputAction.InputAction.Get();

    if (!ensure(IsValid(EnhancedInputComponent)) ||
        !ensure(IsValid(InputAction)))
    {
        return;
    }

    BoundInputComponent = EnhancedInputComponent;

    BindActions(
        *EnhancedInputComponent,
        *InputAction
    );
}

void UBasePlayerInputComponent::Teardown()
{
    if (UEnhancedInputComponent* InputComponent =
        BoundInputComponent.Get())
    {
        InputComponent->ClearBindingsForObject(this);
    }

    BoundInputComponent.Reset();
	this->HandleCanceled();
}

void UBasePlayerInputComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Teardown();
    Super::EndPlay(EndPlayReason);
}

void UBasePlayerInputComponent::BindActions(
    UEnhancedInputComponent& InputComponent,
    const UInputAction& InputAction)
{
	InputComponent.BindAction(
        &InputAction,
        ETriggerEvent::Started,
        this,
        &UBasePlayerInputComponent::HandleStarted
	);
    InputComponent.BindAction(
        &InputAction,
        ETriggerEvent::Completed,
        this,
        &UBasePlayerInputComponent::HandleCompleted
    );
    InputComponent.BindAction(
        &InputAction,
        ETriggerEvent::Canceled,
        this,
        &UBasePlayerInputComponent::HandleCanceled
    );
}

void UBasePlayerInputComponent::HandleStarted()
{
	bIsPressed = true;
}

void UBasePlayerInputComponent::HandleCompleted()
{
	bIsPressed = false;
}

void UBasePlayerInputComponent::HandleCanceled()
{
	bIsPressed = false;
}