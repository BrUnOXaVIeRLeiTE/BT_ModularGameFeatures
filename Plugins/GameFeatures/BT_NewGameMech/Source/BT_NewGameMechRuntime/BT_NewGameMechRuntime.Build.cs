// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class BT_NewGameMechRuntime : ModuleRules
{
	public BT_NewGameMechRuntime(ReadOnlyTargetRules Target) : base(Target)
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
			"CoreUObject", "Engine", "Slate", "SlateCore", "EnhancedInput"
		});

		DynamicallyLoadedModuleNames.AddRange(new string[] {
		});

		PublicIncludePaths.Add(Path.Combine(ModuleDirectory,"Public"));
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory,"Classes"));
		PrivateIncludePaths.Add(Path.Combine(ModuleDirectory,"Private"));
	}
}
