// @lint-ignore-every LICENSELINT
// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class OVRPlatformEngineTelemetry : ModuleRules
{
	public OVRPlatformEngineTelemetry(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "Projects"});

        if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			var dllPath = Path.Combine(ModuleDirectory, "lib", "Win64", "EngineTelemetry.dll");
			RuntimeDependencies.Add(dllPath);
		}
	}
}
