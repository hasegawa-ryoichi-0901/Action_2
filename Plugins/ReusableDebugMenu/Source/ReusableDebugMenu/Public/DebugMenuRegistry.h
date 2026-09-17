#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DebugMenuTypes.h"
#include "DebugMenuRegistry.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDebugMenuRegistryChanged);

/**
 * @brief 正規化されたDebug Menu Treeを保持・検証・検索します。
 *
 * 登録はアトミックに行われ、不正なBatchによってRegistryが部分的に
 * 更新されることはありません。Widget生成やGameplay Stateの処理は担当しません。
 */
UCLASS()
class REUSABLEDEBUGMENU_API UReusableDebugMenuRegistry : public UObject
{
	GENERATED_BODY()

public:
	bool RegisterNode(const FDebugMenuNodeDefinition& Node, FText& OutError);
	bool RegisterNodes(const TArray<FDebugMenuNodeDefinition>& InNodes, FText& OutError);
	bool Contains(FName NodeId) const;
	const FDebugMenuNodeDefinition* FindNode(FName NodeId) const;
	TArray<FDebugMenuNodeDefinition> GetChildren(FName ParentId) const;
	int32 Num() const { return Nodes.Num(); }

	FOnDebugMenuRegistryChanged& OnChanged() { return RegistryChanged; }

private:
	static bool ValidateTree(
		const TMap<FName, FDebugMenuNodeDefinition>& CandidateNodes,
		FText& OutError);

	UPROPERTY(Transient)
	TMap<FName, FDebugMenuNodeDefinition> Nodes;

	FOnDebugMenuRegistryChanged RegistryChanged;
};
