// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class test_ : ModuleRules
{
	public test_(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"GameplayTasks",
			"NavigationSystem",
			"GameplayTags",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			"ALS",
			"ALSCamera",
			"ALSExtras",
			"DeveloperSettings"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"test_",
			"test_/Characters",
			"test_/Characters/AI",
			"test_/Data",
			"test_/Interaction",
			"test_/Variant_Platforming",
			"test_/Variant_Platforming/Animation",
			"test_/Variant_Combat",
			"test_/Variant_Combat/AI",
			"test_/Variant_Combat/Animation",
			"test_/Variant_Combat/Gameplay",
			"test_/Variant_Combat/Interfaces",
			"test_/Variant_Combat/UI",
			"test_/Variant_SideScrolling",
			"test_/Variant_SideScrolling/AI",
			"test_/Variant_SideScrolling/Gameplay",
			"test_/Variant_SideScrolling/Interfaces",
			"test_/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
