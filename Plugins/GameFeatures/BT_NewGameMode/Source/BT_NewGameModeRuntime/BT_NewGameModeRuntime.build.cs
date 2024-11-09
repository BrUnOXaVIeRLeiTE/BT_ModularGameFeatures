// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class BT_NewGameModeRuntime : ModuleRules
{
	public BT_NewGameModeRuntime(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IWYUSupport = IWYUSupport.KeepAsIsForNow;

		PublicDependencyModuleNames.AddRange
		(
			new string[]
			{
				"Core",
				"UMG",
				"InputCore",
				"GameFeatures",
				"GameplayTags",
				"GameplayTasks",
				"ModularGameplay",
				"GameplayAbilities",
				"DeveloperSettings",
				"NetCore",
			}
		);
		
		PrivateDependencyModuleNames.AddRange
		(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
			}
		);

		PublicIncludePaths.Add(Path.Combine(ModuleDirectory,"Public"));
		PrivateIncludePaths.Add(Path.Combine(ModuleDirectory,"Private"));
	}
}
