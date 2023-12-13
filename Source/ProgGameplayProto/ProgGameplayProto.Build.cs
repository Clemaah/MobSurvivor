// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProgGameplayProto : ModuleRules
{
	public ProgGameplayProto(ReadOnlyTargetRules Target) : base(Target)
	{
        PrivateDependencyModuleNames.AddRange(new string[] { "CADKernel" });
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "HTTP", "Json" });
    }
}
