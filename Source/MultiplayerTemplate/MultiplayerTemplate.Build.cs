// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MultiplayerTemplate : ModuleRules
{
	public MultiplayerTemplate(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"DeveloperSettings",
			"OnlineServicesInterface", 
			"CoreOnline",
			"OnlineSubsystem",
			"OnlineSubsystemUtils"
		});
		
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"OnlineServicesEOSGS",
		});
		
		if (Target.Platform == UnrealTargetPlatform.Win64 || Target.Platform == UnrealTargetPlatform.Linux)
        {
            DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
        }
		
		if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PublicDependencyModuleNames.AddRange(new string[]
            {
                "OVRPlatform",
                "OVRPlatformSDK"
            });
        }
		
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
