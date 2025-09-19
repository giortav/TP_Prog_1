// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Tp1 : ModuleRules
{
	public Tp1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Tp1",
			"Tp1/Variant_Platforming",
			"Tp1/Variant_Platforming/Animation",
			"Tp1/Variant_Combat",
			"Tp1/Variant_Combat/AI",
			"Tp1/Variant_Combat/Animation",
			"Tp1/Variant_Combat/Gameplay",
			"Tp1/Variant_Combat/Interfaces",
			"Tp1/Variant_Combat/UI",
			"Tp1/Variant_SideScrolling",
			"Tp1/Variant_SideScrolling/AI",
			"Tp1/Variant_SideScrolling/Gameplay",
			"Tp1/Variant_SideScrolling/Interfaces",
			"Tp1/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
