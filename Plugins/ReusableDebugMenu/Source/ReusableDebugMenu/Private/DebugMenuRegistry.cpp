#include "DebugMenuRegistry.h"

#define LOCTEXT_NAMESPACE "ReusableDebugMenuRegistry"

bool UReusableDebugMenuRegistry::RegisterNode(
	const FDebugMenuNodeDefinition& Node,
	FText& OutError)
{
	return RegisterNodes({Node}, OutError);
}

bool UReusableDebugMenuRegistry::RegisterNodes(
	const TArray<FDebugMenuNodeDefinition>& InNodes,
	FText& OutError)
{
	TSet<FName> BatchIds;
	TMap<FName, FDebugMenuNodeDefinition> CandidateNodes = Nodes;

	for (const FDebugMenuNodeDefinition& Node : InNodes)
	{
		if (Node.NodeId.IsNone())
		{
			OutError = LOCTEXT("MissingNodeId", "A debug menu node has no NodeId.");
			return false;
		}

		if (BatchIds.Contains(Node.NodeId))
		{
			OutError = FText::Format(
				LOCTEXT("DuplicateBatchNode", "NodeId '{0}' appears more than once in the same registration batch."),
				FText::FromName(Node.NodeId));
			return false;
		}

		BatchIds.Add(Node.NodeId);
		CandidateNodes.Add(Node.NodeId, Node);
	}

	if (!ValidateTree(CandidateNodes, OutError))
	{
		return false;
	}

	Nodes = MoveTemp(CandidateNodes);
	RegistryChanged.Broadcast();
	OutError = FText::GetEmpty();
	return true;
}

bool UReusableDebugMenuRegistry::Contains(const FName NodeId) const
{
	return Nodes.Contains(NodeId);
}

const FDebugMenuNodeDefinition* UReusableDebugMenuRegistry::FindNode(const FName NodeId) const
{
	return Nodes.Find(NodeId);
}

TArray<FDebugMenuNodeDefinition> UReusableDebugMenuRegistry::GetChildren(
	const FName ParentId) const
{
	TArray<FDebugMenuNodeDefinition> Result;

	for (const TPair<FName, FDebugMenuNodeDefinition>& Pair : Nodes)
	{
		if (Pair.Value.ParentId == ParentId)
		{
			Result.Add(Pair.Value);
		}
	}

	Result.Sort([](const FDebugMenuNodeDefinition& Left, const FDebugMenuNodeDefinition& Right)
	{
		if (Left.SortOrder != Right.SortOrder)
		{
			return Left.SortOrder < Right.SortOrder;
		}

		return Left.NodeId.LexicalLess(Right.NodeId);
	});

	return Result;
}

bool UReusableDebugMenuRegistry::ValidateTree(
	const TMap<FName, FDebugMenuNodeDefinition>& CandidateNodes,
	FText& OutError)
{
	for (const TPair<FName, FDebugMenuNodeDefinition>& Pair : CandidateNodes)
	{
		const FDebugMenuNodeDefinition& Node = Pair.Value;
		if (Pair.Key != Node.NodeId || Node.NodeId.IsNone())
		{
			OutError = LOCTEXT("InvalidMapKey", "The registry contains an invalid NodeId.");
			return false;
		}

		if (Node.DisplayName.IsEmpty())
		{
			OutError = FText::Format(
				LOCTEXT("MissingDisplayName", "Node '{0}' has no DisplayName."),
				FText::FromName(Node.NodeId));
			return false;
		}

		if (Node.NodeId == Node.ParentId)
		{
			OutError = FText::Format(
				LOCTEXT("SelfParent", "Node '{0}' cannot be its own parent."),
				FText::FromName(Node.NodeId));
			return false;
		}

		if (!Node.ParentId.IsNone())
		{
			const FDebugMenuNodeDefinition* Parent = CandidateNodes.Find(Node.ParentId);
			if (Parent == nullptr)
			{
				OutError = FText::Format(
					LOCTEXT("MissingParent", "Node '{0}' refers to missing parent '{1}'."),
					FText::FromName(Node.NodeId),
					FText::FromName(Node.ParentId));
				return false;
			}

			if (Parent->NodeType != EDebugMenuNodeType::Category)
			{
				OutError = FText::Format(
					LOCTEXT("NonCategoryParent", "Node '{0}' has non-category parent '{1}'."),
					FText::FromName(Node.NodeId),
					FText::FromName(Node.ParentId));
				return false;
			}
		}

		TSet<FName> Ancestors;
		FName NextParentId = Node.ParentId;
		while (!NextParentId.IsNone())
		{
			if (Ancestors.Contains(NextParentId) || NextParentId == Node.NodeId)
			{
				OutError = FText::Format(
					LOCTEXT("Cycle", "Node '{0}' is part of a parent cycle."),
					FText::FromName(Node.NodeId));
				return false;
			}

			Ancestors.Add(NextParentId);
			const FDebugMenuNodeDefinition* Parent = CandidateNodes.Find(NextParentId);
			if (Parent == nullptr)
			{
				break;
			}
			NextParentId = Parent->ParentId;
		}
	}

	return true;
}

#undef LOCTEXT_NAMESPACE
