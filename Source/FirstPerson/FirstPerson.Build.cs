// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FirstPerson : ModuleRules
{
	public FirstPerson(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"Engine",
			"InputCore",
			"CoreUObject",
			"GameFeatures",
			"GameplayTags",
			"GameplayTasks",
			"EnhancedInput",
			"ModularGameplay",
			"GameplayAbilities"
		});
	}
}
