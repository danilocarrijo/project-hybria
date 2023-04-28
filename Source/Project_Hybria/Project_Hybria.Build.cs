// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Project_Hybria : ModuleRules
{
	public Project_Hybria(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
