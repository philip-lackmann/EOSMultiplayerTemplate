#pragma once

#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogPSDKEngineTelemetry, Log, All);

class OVRPLATFORMENGINETELEMETRY_API FOVRPlatformEngineTelemetryModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	// Wrapper functions
	static void InitTelemetry();
	static void ShutDownTelemetry();
	static bool GetUnifiedConsent(int ConsentType);
	static bool SendUnifiedEvent(
	    int isEssential,
	    const char* productType,
	    const char* eventName,
	    const char* event_metadata_json,
	    const char* project_name = "",
	    const char* event_entrypoint = "",
	    const char* project_guid = "",
	    const char* event_type = "",
	    const char* event_target = "",
	    const char* error_msg = "",
	    const char* is_internal_build = "",
	    const char* batch_mode = ""
	);

private:
	// Function pointers for DLL functions
	typedef void (*EngineTelemetryInitType)();
	typedef void (*EngineTelemetryShutDownType)();
	typedef bool (*EngineTelemetrySendEventType)(const char*, const char*, const char*);
	typedef bool (*EngineTelemetryGetUnifiedConsentType)(int);
	typedef bool (*EngineTelemetrySendUnifiedEventType)(
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
		const char* batch_mode);

	static EngineTelemetryInitType EngineTelemetryInit;
	static EngineTelemetryShutDownType EngineTelemetryShutDown;
	static EngineTelemetryGetUnifiedConsentType EngineTelemetryGetUnifiedConsent;
	static EngineTelemetrySendUnifiedEventType EngineTelemetrySendUnifiedEvent;
};
