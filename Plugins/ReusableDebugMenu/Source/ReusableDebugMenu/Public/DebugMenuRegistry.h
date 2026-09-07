#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DebugMenuTypes.h"
#include "DebugMenuRegistry.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDebugMenuRegistryChanged);

/**
 * Owns and validates the menu tree. Mutations are atomic: an invalid batch never
 * leaves a partially updated registry.
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
