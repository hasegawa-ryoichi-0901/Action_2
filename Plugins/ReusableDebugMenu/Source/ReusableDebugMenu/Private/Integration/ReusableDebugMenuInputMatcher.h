#pragma once

struct FKeyEvent;
class UEnhancedPlayerInput;
class UEnhancedInputLocalPlayerSubsystem;
class UInputAction;

/**
 * @brief Debug Menu Toggle Action用のStatelessなEnhanced Input Matcherです。
 *
 * MappingされたKeyとChord Triggerの判定だけを行い、Input Bindingの登録や
 * Menu Stateの変更は行いません。
 */
struct FReusableDebugMenuInputMatcher
{
	static bool Matches(
		const UInputAction& Action,
		const UEnhancedPlayerInput& PlayerInput,
		const UEnhancedInputLocalPlayerSubsystem& InputSubsystem,
		const FKeyEvent& KeyEvent);
};
