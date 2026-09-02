#pragma once

#include "CoreMinimal.h"
#include "DebugMenuTypes.generated.h"

UENUM(BlueprintType)
enum class EDebugMenuNodeType : uint8
{
	Category,
	Command
};

/**
 * A stable, presentation-independent definition for one node in the debug menu tree.
 * NodeId and ParentId are identifiers; DisplayName is presentation text only.
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
