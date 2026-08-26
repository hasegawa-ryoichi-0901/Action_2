// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Action_2 : ModuleRules
{
	public Action_2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[] {
				"Core",
				"CoreUObject",
				"Engine",
				"InputCore",
				"EnhancedInput",
				"GameplayTags",
				"UMG" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
		PublicIncludePaths.AddRange(new string[]
		{
			"Action_2",
			"Action_2/Characters/",
			"Action_2/Input/",
			"Action_2/Input/Interface/"
		});

	}
}
