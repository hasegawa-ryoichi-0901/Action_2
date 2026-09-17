#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

REUSABLEDEBUGMENU_API DECLARE_LOG_CATEGORY_EXTERN(LogReusableDebugMenu, Log, All);

/**
 * @brief ReusableDebugMenuプラグインのモジュールエントリポイントを定義します。
 *
 * ランタイムの振る舞いはLocalPlayer SubsystemとIntegration Componentが
 * 所有し、このクラスはモジュールの起動・終了に限定されます。
 */
class FReusableDebugMenuModule final : public IModuleInterface
{
};
