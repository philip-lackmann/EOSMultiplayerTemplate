# Unreal Engine Multiplayer Template

- Unreal Engine 5.7.2
- Epic Online Services (EOS)

WIP: The aim of this template is to build a minimal basis for co-op games with cross-platform support
for Steam and Meta / Oculus.

The project uses the newer Online Services API (OSSv2), which Epic says will eventually replace Online Subsystem (OSSv1).
However, OSSv2 is still under development and not recommended for production. Occasionally OSSv1 is still used in this project
where needed, specifically to receive tokens for the EOS identity providers.

Expect changes as Epic develops OSSv2 further.

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

2. Setup EOS Client
...

3. Setup EOS Identity Providers
...

## 2.0 Supported Platforms / External Tokens
###  Steam Ticket
Implemented and testable using Spacewar as app id.

### Meta User ID and Nonce
Technically implemented, but not to be tested in the near future.
Meta does not seem to offer any easy way to test this as dev. For this to work the app needs to signed, 
distributed on a release channel and worst of all a data usage checkup (DUC) needs to be completed, 
requesting permissions to read the logged in user id, which need to be approved by meta after filling in a compliance form.
