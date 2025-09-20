// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TpProg1 : ModuleRules
{
	public TpProg1(ReadOnlyTargetRules Target) : base(Target)
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
			"TpProg1",
			"TpProg1/Variant_Platforming",
			"TpProg1/Variant_Platforming/Animation",
			"TpProg1/Variant_Combat",
			"TpProg1/Variant_Combat/AI",
			"TpProg1/Variant_Combat/Animation",
			"TpProg1/Variant_Combat/Gameplay",
			"TpProg1/Variant_Combat/Interfaces",
			"TpProg1/Variant_Combat/UI",
			"TpProg1/Variant_SideScrolling",
			"TpProg1/Variant_SideScrolling/AI",
			"TpProg1/Variant_SideScrolling/Gameplay",
			"TpProg1/Variant_SideScrolling/Interfaces",
			"TpProg1/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
