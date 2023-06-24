// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Multimask_Prototype : ModuleRules
{
    public Multimask_Prototype(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "UMG" }); // Include "UMG" module here

        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}
