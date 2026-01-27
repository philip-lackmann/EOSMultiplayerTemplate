# Unreal Engine Multiplayer Template

- Unreal Engine 5.7.2
- Epic Online Services (EOS)

## 1.0 Getting Started

### 1.1 (Optional) Migrating Into An Existing Project
1. Configure EOS
Add the following to DefaultEngine.ini:
````
[OnlineServices]
DefaultServices=Epic

[/Script/Engine.Engine]
!NetDriverDefinitions=ClearArray
+NetDriverDefinitions=(DefName="GameNetDriver",DriverClassName="SocketSubsystemEOS.NetDriverEOSBase",DriverClassNameFallback="OnlineSubsystemUtils.IpNetDriver")
+NetDriverDefinitions=(DefName="DemoNetDriver",DriverClassName="/Script/Engine.DemoNetDriver",DriverClassNameFallback="/Script/Engine.DemoNetDriver")

[/Script/Engine.GameEngine]
!NetDriverDefinitions=ClearArray
+NetDriverDefinitions=(DefName="GameNetDriver",DriverClassName="SocketSubsystemEOS.NetDriverEOSBase",DriverClassNameFallback="OnlineSubsystemUtils.IpNetDriver")
+NetDriverDefinitions=(DefName="DemoNetDriver",DriverClassName="/Script/Engine.DemoNetDriver",DriverClassNameFallback="/Script/Engine.DemoNetDriver")

[OnlineServices.EOS]
ProductId=PRODUCT_ID
SandboxId=SANDBOX_ID
DeploymentId=DEPLOYTMENT_ID
ClientId=CLIENT_ID
ClientSecret=CLIENT_SECRET
ClientEncryptionKey=CLIENT_ENCRYPTION_KEY
````

2. Add DeveloperSettings, OnlineServicesInterface and CoreOnline to your .Build.cs public dependencies. 
Your .Build.cs file should look like this:

````
PublicDependencyModuleNames.AddRange(new string[] {
    "Core",
    "CoreUObject",
    "Engine",
    "InputCore",
    "EnhancedInput",
    "DeveloperSettings",
    "OnlineServicesInterface", 
    "CoreOnline",
});
````

3. Configure Game Classes
Under Project Settings > Maps & Modes set the game instance class to OnlineGameInstance.

### 1.2 Setup
1. Setup EOS Product
Configure your product in the [Epic Developer Portal](https://dev.epicgames.com/portal/en-US/).
Replace the values in DefaultEngine.ini with those from your product settings:
````
[OnlineServices.EOS]
ProductId=PRODUCT_ID
SandboxId=SANDBOX_ID
DeploymentId=DEPLOYTMENT_ID
ClientId=CLIENT_ID
ClientSecret=CLIENT_SECRET
ClientEncryptionKey=CLIENT_ENCRYPTION_KEY
````

