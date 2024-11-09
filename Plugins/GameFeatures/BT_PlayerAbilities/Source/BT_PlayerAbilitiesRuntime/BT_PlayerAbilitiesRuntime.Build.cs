// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class BT_PlayerAbilitiesRuntime : ModuleRules
{
	public BT_PlayerAbilitiesRuntime(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IWYUSupport = IWYUSupport.KeepAsIsForNow;

		PublicIncludePaths.AddRange(new string[] {
		});

		PrivateIncludePaths.AddRange(new string[] {
		});

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
		});

		PrivateDependencyModuleNames.AddRange(new string[] {
			"CoreUObject", "Engine"
		});

		DynamicallyLoadedModuleNames.AddRange(new string[] {
		});

		PublicIncludePaths.Add(Path.Combine(ModuleDirectory,"Public"));
		PrivateIncludePaths.Add(Path.Combine(ModuleDirectory,"Private"));
	}
}
