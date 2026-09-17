#pragma once

#include "CoreMinimal.h"
#include "DebugMenuTypes.generated.h"

struct FKeyEvent;

/** Host ProjectがFocused UI上のDebug Menu Toggle Inputを識別するためのMatcherです。 */
DECLARE_DELEGATE_RetVal_OneParam(bool, FDebugMenuToggleInputMatcher, const FKeyEvent&);

UENUM(BlueprintType)
/** @brief ノードが子ノードへの移動かCommand実行かを識別します。 */
enum class EDebugMenuNodeType : uint8
{
	Category,
	Command
};

/**
 * @brief Debug Menuの1ノードを表す、表示層に依存しない安定した定義です。
 *
 * NodeIdとParentIdは永続的な識別子です。DisplayNameは表示用テキストであり、
 * 検索キーとして使用してはいけません。
 */
USTRUCT(BlueprintType)
struct REUSABLEDEBUGMENU_API FDebugMenuNodeDefinition
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug Menu")
	FName NodeId = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug Menu")
	FName ParentId = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug Menu")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug Menu")
	EDebugMenuNodeType NodeType = EDebugMenuNodeType::Category;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug Menu")
	int32 SortOrder = 0;
};
