#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DebugMenuTypes.h"
#include "DebugMenuCatalog.generated.h"

class UReusableDebugMenuWindow;

/**
 * @brief Menu Node定義とプロジェクト所有のUMG Adapterを関連付けます。
 *
 * CategoryにはWindowClassを設定せず、Command Nodeには具象の
 * UReusableDebugMenuWindow派生クラスを設定します。
 */
USTRUCT(BlueprintType)
struct REUSABLEDEBUGMENU_API FDebugMenuCatalogEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debug Menu")
	FDebugMenuNodeDefinition Node;

	UPROPERTY(
		EditAnywhere,
		BlueprintReadOnly,
		Category = "Debug Menu",
		meta = (ToolTip = "Command の場合だけ設定します。Category では空にしてください。"))
	TSubclassOf<UReusableDebugMenuWindow> WindowClass;
};

/**
 * @brief プロジェクト固有のMenu内容をSubsystemへ提供するDataAssetです。
 *
 * PluginはMenuの検証と実行フローを担当し、Host ProjectはこのAssetと、
 * Assetから参照されるCommand Window Classを所有します。
 */
UCLASS(BlueprintType)
class REUSABLEDEBUGMENU_API UReusableDebugMenuCatalog : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debug Menu")
	TArray<FDebugMenuCatalogEntry> Entries;
};
