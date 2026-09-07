#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DebugMenuTypes.h"
#include "DebugMenuCatalog.generated.h"

class UReusableDebugMenuWindow;

/** Outer-layer binding between a core command and its UMG adapter. */
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

/** Project-specific menu content. The plugin owns behavior; projects own this data. */
UCLASS(BlueprintType)
class REUSABLEDEBUGMENU_API UReusableDebugMenuCatalog : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debug Menu")
	TArray<FDebugMenuCatalogEntry> Entries;
};
