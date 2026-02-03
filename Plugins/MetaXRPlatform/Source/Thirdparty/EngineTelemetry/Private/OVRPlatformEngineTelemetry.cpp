
#include "OVRPlatformEngineTelemetry.h"
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/App.h"
#include "Misc/Paths.h"
#include "HAL/PlatformProcess.h"

IMPLEMENT_MODULE(FOVRPlatformEngineTelemetryModule, OVRPlatformEngineTelemetry)
DEFINE_LOG_CATEGORY(LogPSDKEngineTelemetry);

FOVRPlatformEngineTelemetryModule::EngineTelemetryInitType FOVRPlatformEngineTelemetryModule::EngineTelemetryInit = nullptr;
FOVRPlatformEngineTelemetryModule::EngineTelemetryShutDownType FOVRPlatformEngineTelemetryModule::EngineTelemetryShutDown = nullptr;
FOVRPlatformEngineTelemetryModule::EngineTelemetryGetUnifiedConsentType FOVRPlatformEngineTelemetryModule::EngineTelemetryGetUnifiedConsent = nullptr;
FOVRPlatformEngineTelemetryModule::EngineTelemetrySendUnifiedEventType FOVRPlatformEngineTelemetryModule::EngineTelemetrySendUnifiedEvent = nullptr;

void FOVRPlatformEngineTelemetryModule::StartupModule()
{
#if PLATFORM_WINDOWS
	const FString BaseDir = IPluginManager::Get().FindPlugin("OculusPlatform")->GetBaseDir();
	const FString DllPath = FPaths::Combine(*BaseDir, TEXT("Source/Thirdparty/EngineTelemetry/lib/Win64/EngineTelemetry.dll"));
	void* DllHandle = FPlatformProcess::GetDllHandle(*DllPath);

	if (DllHandle)
	{
		UE_LOG(LogPSDKEngineTelemetry, Log, TEXT("Successfully loaded EngineTelemetry dll."));
		EngineTelemetryInit = (EngineTelemetryInitType)FPlatformProcess::GetDllExport(DllHandle, TEXT("engineTelemetry_Init"));
		EngineTelemetryShutDown = (EngineTelemetryShutDownType)FPlatformProcess::GetDllExport(DllHandle, TEXT("engineTelemetry_ShutDown"));
		EngineTelemetryGetUnifiedConsent = (EngineTelemetryGetUnifiedConsentType)FPlatformProcess::GetDllExport(DllHandle, TEXT("engineTelemetry_GetUnifiedConsent"));
		EngineTelemetrySendUnifiedEvent = (EngineTelemetrySendUnifiedEventType)FPlatformProcess::GetDllExport(DllHandle, TEXT("engineTelemetry_SendUnifiedEvent"));

		if (EngineTelemetryInit && EngineTelemetryShutDown && EngineTelemetryGetUnifiedConsent && EngineTelemetrySendUnifiedEvent)
		{
			UE_LOG(LogPSDKEngineTelemetry, Log, TEXT("Successfully bound all functions."));
			InitTelemetry();
		}
		else
		{
			UE_LOG(LogPSDKEngineTelemetry, Error, TEXT("Failed to bind one or more functions."));
		}
	}
	else
	{
		UE_LOG(LogPSDKEngineTelemetry, Error, TEXT("Failed to load EngineTelemetry.dll."));
	}
#endif
}

void FOVRPlatformEngineTelemetryModule::ShutdownModule()
{
#if PLATFORM_WINDOWS
	ShutDownTelemetry();
	EngineTelemetryInit = nullptr;
	EngineTelemetryShutDown = nullptr;
	EngineTelemetryGetUnifiedConsent = nullptr;
	EngineTelemetrySendUnifiedEvent = nullptr;
#endif
}

void FOVRPlatformEngineTelemetryModule::InitTelemetry()
{
#if PLATFORM_WINDOWS
	if (EngineTelemetryInit)
	{
		EngineTelemetryInit();
	}
	else
	{
		UE_LOG(LogPSDKEngineTelemetry, Error, TEXT("Init function not bound."));
	}
#endif
}

void FOVRPlatformEngineTelemetryModule::ShutDownTelemetry()
{
#if PLATFORM_WINDOWS
	if (EngineTelemetryShutDown)
	{
		EngineTelemetryShutDown();
	}
	else
	{
		UE_LOG(LogPSDKEngineTelemetry, Error, TEXT("ShutDown function not bound."));
	}
#endif
}

bool FOVRPlatformEngineTelemetryModule::GetUnifiedConsent(int ConsentType)
{
#if PLATFORM_WINDOWS
	if (EngineTelemetryGetUnifiedConsent)
	{
		return EngineTelemetryGetUnifiedConsent(ConsentType);
	}
	else
	{
		UE_LOG(LogPSDKEngineTelemetry, Error, TEXT("GetUnifiedConsent function not bound."));
		return false;
	}
#else
	return false;
#endif
}

bool FOVRPlatformEngineTelemetryModule::SendUnifiedEvent(
	int isEssential,
	const char* productType,
	const char* eventName,
	const char* event_metadata_json,
	const char* project_name,
	const char* event_entrypoint,
	const char* project_guid,
	const char* event_type,
	const char* event_target,
	const char* error_msg,
	const char* is_internal_build,
	const char* batch_mode)
{
#if PLATFORM_WINDOWS
	const char* ProjectNameCStr = project_name;
	if (ProjectNameCStr == nullptr || ProjectNameCStr[0] == '\0')
	{
		FString ProjectNameStr = FApp::GetProjectName();
		ProjectNameCStr = TCHAR_TO_UTF8(*ProjectNameStr);
	}

	if (EngineTelemetrySendUnifiedEvent)
	{
		return EngineTelemetrySendUnifiedEvent(
			isEssential,
			productType,
			eventName,
			event_metadata_json,
			ProjectNameCStr,
			event_entrypoint,
			project_guid,
			event_type,
			event_target,
			error_msg,
			is_internal_build,
			batch_mode);
	}
	else
	{
		UE_LOG(LogPSDKEngineTelemetry, Error, TEXT("SendUnifiedEvent function not bound."));
		return false;
	}
#else
	return false;
#endif
}
