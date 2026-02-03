// Copyright (c) Meta Platforms, Inc. and affiliates.

// This file was @generated with LibOVRPlatform/codegen/main. Do not modify it!

#include "OVRPlatformFunctions.h"
#include "OVRPlatformRequestsConverters.h"
#include "OVRPlatformOptionsConverters.h"
#include "OVRPlatformEngineTelemetry.h"


// ----------------------------------------------------------------------
// ApplicationLifecycle

FOvrLaunchDetails UOvrFunctionsBlueprintLibrary::ApplicationLifecycle_GetLaunchDetails()
{
    FOVRPlatformEngineTelemetryModule::SendUnifiedEvent(1, "platform_sdk", "PSDK_ApplicationLifecycle_GetLaunchDetails", "", "");
    return FOvrLaunchDetails(ovr_ApplicationLifecycle_GetLaunchDetails(), TOvrMessageHandlePtr());
}

void UOvrFunctionsBlueprintLibrary::ApplicationLifecycle_LogDeeplinkResult(FString TrackingID, EOvrLaunchResult Result)
{
    FOVRPlatformEngineTelemetryModule::SendUnifiedEvent(1, "platform_sdk", "PSDK_ApplicationLifecycle_LogDeeplinkResult", "", "");
    ovr_ApplicationLifecycle_LogDeeplinkResult(TCHAR_TO_UTF8(*TrackingID), ConvertLaunchResult(Result));
}

// ----------------------------------------------------------------------
// Voip

void UOvrFunctionsBlueprintLibrary::Voip_Accept(FOvrId UserID)
{
    FOVRPlatformEngineTelemetryModule::SendUnifiedEvent(1, "platform_sdk", "PSDK_Voip_Accept", "", "");
    ovr_Voip_Accept(static_cast<ovrID>(UserID));
}

EOvrVoipDtxState UOvrFunctionsBlueprintLibrary::Voip_GetIsConnectionUsingDtx(FOvrId PeerID)
{
    FOVRPlatformEngineTelemetryModule::SendUnifiedEvent(1, "platform_sdk", "PSDK_Voip_GetIsConnectionUsingDtx", "", "");
    return ConvertVoipDtxState(ovr_Voip_GetIsConnectionUsingDtx(static_cast<ovrID>(PeerID)));
}

EOvrVoipBitrate UOvrFunctionsBlueprintLibrary::Voip_GetLocalBitrate(FOvrId PeerID)
{
    FOVRPlatformEngineTelemetryModule::SendUnifiedEvent(1, "platform_sdk", "PSDK_Voip_GetLocalBitrate", "", "");
    return ConvertVoipBitrate(ovr_Voip_GetLocalBitrate(static_cast<ovrID>(PeerID)));
}

int64 UOvrFunctionsBlueprintLibrary::Voip_GetOutputBufferMaxSize()
{
    FOVRPlatformEngineTelemetryModule::SendUnifiedEvent(1, "platform_sdk", "PSDK_Voip_GetOutputBufferMaxSize", "", "");
    return static_cast<int64>(ovr_Voip_GetOutputBufferMaxSize());
}

int64 UOvrFunctionsBlueprintLibrary::Voip_GetPCMSize(FOvrId SenderID)
{
    FOVRPlatformEngineTelemetryModule::SendUnifiedEvent(1, "platform_sdk", "PSDK_Voip_GetPCMSize", "", "");
    return static_cast<int64>(ovr_Voip_GetPCMSize(static_cast<ovrID>(SenderID)));
}

EOvrVoipBitrate UOvrFunctionsBlueprintLibrary::Voip_GetRemoteBitrate(FOvrId PeerID)
{
    FOVRPlatformEngineTelemetryModule::SendUnifiedEvent(1, "platform_sdk", "PSDK_Voip_GetRemoteBitrate", "", "");
    return ConvertVoipBitrate(ovr_Voip_GetRemoteBitrate(static_cast<ovrID>(PeerID)));
}

int32 UOvrFunctionsBlueprintLibrary::Voip_GetSyncTimestamp(FOvrId UserID)
{
    FOVRPlatformEngineTelemetryModule::SendUnifiedEvent(1, "platform_sdk", "PSDK_Voip_GetSyncTimestamp", "", "");
    return static_cast<int32>(ovr_Voip_GetSyncTimestamp(static_cast<ovrID>(UserID)));
}

int64 UOvrFunctionsBlueprintLibrary::Voip_GetSyncTimestampDifference(int32 Lhs, int32 Rhs)
{
    FOVRPlatformEngineTelemetryModule::SendUnifiedEvent(1, "platform_sdk", "PSDK_Voip_GetSyncTimestampDifference", "", "");
    return static_cast<int64>(ovr_Voip_GetSyncTimestampDifference(static_cast<uint32_t>(Lhs), static_cast<uint32_t>(Rhs)));
}

EOvrVoipMuteState UOvrFunctionsBlueprintLibrary::Voip_GetSystemVoipMicrophoneMuted()
{
    FOVRPlatformEngineTelemetryModule::SendUnifiedEvent(1, "platform_sdk", "PSDK_Voip_GetSystemVoipMicrophoneMuted", "", "");
    return ConvertVoipMuteState(ovr_Voip_GetSystemVoipMicrophoneMuted());
}

EOvrSystemVoipStatus UOvrFunctionsBlueprintLibrary::Voip_GetSystemVoipStatus()
{
    FOVRPlatformEngineTelemetryModule::SendUnifiedEvent(1, "platform_sdk", "PSDK_Voip_GetSystemVoipStatus", "", "");
    return ConvertSystemVoipStatus(ovr_Voip_GetSystemVoipStatus());
}

void UOvrFunctionsBlueprintLibrary::Voip_SetMicrophoneMuted(EOvrVoipMuteState State)
{
    FOVRPlatformEngineTelemetryModule::SendUnifiedEvent(1, "platform_sdk", "PSDK_Voip_SetMicrophoneMuted", "", "");
    ovr_Voip_SetMicrophoneMuted(ConvertVoipMuteState(State));
}

void UOvrFunctionsBlueprintLibrary::Voip_SetNewConnectionOptions(FOvrVoipOptions VoipOptions)
{
    FOVRPlatformEngineTelemetryModule::SendUnifiedEvent(1, "platform_sdk", "PSDK_Voip_SetNewConnectionOptions", "", "");
    ovr_Voip_SetNewConnectionOptions(FOvrVoipOptionsConverter(VoipOptions));
}

void UOvrFunctionsBlueprintLibrary::Voip_SetOutputSampleRate(EOvrVoipSampleRate Rate)
{
    FOVRPlatformEngineTelemetryModule::SendUnifiedEvent(1, "platform_sdk", "PSDK_Voip_SetOutputSampleRate", "", "");
    ovr_Voip_SetOutputSampleRate(ConvertVoipSampleRate(Rate));
}

void UOvrFunctionsBlueprintLibrary::Voip_Start(FOvrId UserID)
{
    FOVRPlatformEngineTelemetryModule::SendUnifiedEvent(1, "platform_sdk", "PSDK_Voip_Start", "", "");
    ovr_Voip_Start(static_cast<ovrID>(UserID));
}

void UOvrFunctionsBlueprintLibrary::Voip_Stop(FOvrId UserID)
{
    FOVRPlatformEngineTelemetryModule::SendUnifiedEvent(1, "platform_sdk", "PSDK_Voip_Stop", "", "");
    ovr_Voip_Stop(static_cast<ovrID>(UserID));
}

bool UOvrFunctionsBlueprintLibrary::Platform_IsInitialized()
{
    FOVRPlatformEngineTelemetryModule::SendUnifiedEvent(1, "platform_sdk", "PSDK_Platform_IsInitialized", "", "");
    return ovr_IsPlatformInitialized();
}

FOvrId UOvrFunctionsBlueprintLibrary::Platform_GetLoggedInUserID()
{
    FOVRPlatformEngineTelemetryModule::SendUnifiedEvent(1, "platform_sdk", "PSDK_Platform_GetLoggedInUserID", "", "");
    return FOvrId(ovr_GetLoggedInUserID());
}

FString UOvrFunctionsBlueprintLibrary::Platform_GetLoggedInUserLocale()
{
    FOVRPlatformEngineTelemetryModule::SendUnifiedEvent(1, "platform_sdk", "PSDK_Platform_GetLoggedInUserLocale", "", "");
    return UTF8_TO_TCHAR(ovr_GetLoggedInUserLocale());
}

void UOvrFunctionsBlueprintLibrary::Platform_SetDeveloperAccessToken(FString AccessToken)
{
    FOVRPlatformEngineTelemetryModule::SendUnifiedEvent(1, "platform_sdk", "PSDK_Platform_SetDeveloperAccessToken", "", "");
    ovr_SetDeveloperAccessToken(TCHAR_TO_UTF8(*AccessToken));
}
