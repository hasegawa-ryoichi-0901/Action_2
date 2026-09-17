#include "Integration/ReusableDebugMenuInputMatcher.h"

#include "EnhancedPlayerInput.h"
#include "EnhancedInputSubsystems.h"
#include "Input/Events.h"
#include "InputAction.h"
#include "InputTriggers.h"

namespace
{
	bool AreChordTriggersSatisfied(
		const TArray<TObjectPtr<UInputTrigger>>& Triggers,
		const UEnhancedPlayerInput& PlayerInput)
	{
		for (const UInputTrigger* Trigger : Triggers)
		{
			const UInputTriggerChordAction* ChordTrigger =
				Cast<UInputTriggerChordAction>(Trigger);
			if (!IsValid(ChordTrigger))
			{
				continue;
			}

			const FInputActionInstance* ChordInstance = IsValid(ChordTrigger->ChordAction)
				? PlayerInput.FindActionInstanceData(ChordTrigger->ChordAction)
				: nullptr;
			const bool bChordTriggered =
				ChordInstance != nullptr &&
				ChordInstance->GetTriggerEvent() == ETriggerEvent::Triggered;

			if (Trigger->IsA<UInputTriggerChordBlocker>())
			{
				if (bChordTriggered)
				{
					return false;
				}
			}
			else if (!bChordTriggered)
			{
				return false;
			}
		}

		return true;
	}
}

bool FReusableDebugMenuInputMatcher::Matches(
	const UInputAction& Action,
	const UEnhancedPlayerInput& PlayerInput,
	const UEnhancedInputLocalPlayerSubsystem& InputSubsystem,
	const FKeyEvent& KeyEvent)
{
	return AreChordTriggersSatisfied(Action.Triggers, PlayerInput) &&
		InputSubsystem.QueryKeysMappedToAction(&Action).Contains(
			KeyEvent.GetKey());
}
