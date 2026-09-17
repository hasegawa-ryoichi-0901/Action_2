#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"

#include "DebugMenuRegistry.h"

namespace
{
FDebugMenuNodeDefinition MakeCategory(
	const FName NodeId,
	const FName ParentId = NAME_None)
{
	FDebugMenuNodeDefinition Node;
	Node.NodeId = NodeId;
	Node.ParentId = ParentId;
	Node.DisplayName = FText::FromName(NodeId);
	Node.NodeType = EDebugMenuNodeType::Category;
	return Node;
}
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FDebugMenuRegistryAdversarialTest,
	"ReusableDebugMenu.Registry.AdversarialValidation",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDebugMenuRegistryAdversarialTest::RunTest(const FString& Parameters)
{
	UReusableDebugMenuRegistry* Registry = NewObject<UReusableDebugMenuRegistry>();
	FText Error;

	const FDebugMenuNodeDefinition Root = MakeCategory(TEXT("Root"));
	const FDebugMenuNodeDefinition Child = MakeCategory(TEXT("Child"), TEXT("Root"));
	TestTrue(
		TEXT("An unordered but valid tree is accepted atomically"),
		Registry->RegisterNodes({Child, Root}, Error));
	TestEqual(TEXT("Valid nodes are retained"), Registry->Num(), 2);
	TestEqual(TEXT("Child lookup returns one node"), Registry->GetChildren(TEXT("Root")).Num(), 1);

	TestFalse(
		TEXT("A missing parent is rejected"),
		Registry->RegisterNode(MakeCategory(TEXT("Orphan"), TEXT("Missing")), Error));
	TestEqual(TEXT("A failed mutation leaves the registry unchanged"), Registry->Num(), 2);

	TestFalse(
		TEXT("A self-parent is rejected"),
		Registry->RegisterNode(MakeCategory(TEXT("Self"), TEXT("Self")), Error));

	const FDebugMenuNodeDefinition CycleA = MakeCategory(TEXT("CycleA"), TEXT("CycleB"));
	const FDebugMenuNodeDefinition CycleB = MakeCategory(TEXT("CycleB"), TEXT("CycleA"));
	TestFalse(
		TEXT("A multi-node cycle is rejected"),
		Registry->RegisterNodes({CycleA, CycleB}, Error));

	TestFalse(
		TEXT("Duplicate IDs in one batch are rejected"),
		Registry->RegisterNodes({MakeCategory(TEXT("Duplicate")), MakeCategory(TEXT("Duplicate"))}, Error));

	FDebugMenuNodeDefinition EmptyLabel = MakeCategory(TEXT("EmptyLabel"));
	EmptyLabel.DisplayName = FText::GetEmpty();
	TestFalse(TEXT("An empty display name is rejected"), Registry->RegisterNode(EmptyLabel, Error));

	FDebugMenuNodeDefinition Command;
	Command.NodeId = TEXT("Command");
	Command.DisplayName = FText::FromString(TEXT("Command"));
	Command.NodeType = EDebugMenuNodeType::Command;
	const FDebugMenuNodeDefinition ChildOfCommand =
		MakeCategory(TEXT("ChildOfCommand"), TEXT("Command"));
	TestFalse(
		TEXT("A command cannot own child nodes"),
		Registry->RegisterNodes({Command, ChildOfCommand}, Error));

	TestEqual(TEXT("All invalid mutations were atomic"), Registry->Num(), 2);
	return true;
}

#endif
