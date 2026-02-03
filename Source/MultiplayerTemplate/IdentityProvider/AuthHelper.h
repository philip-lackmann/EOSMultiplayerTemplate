#pragma once
#include "IExternalTokenProvider.h"
#include "Online/Auth.h"

enum Platform
{
	STEAM,
	OCULUS,
	DEV
};

static FString PlatformToString(const Platform InPlatform)
{
	switch (InPlatform)
	{
		case STEAM:  return TEXT("STEAM");
		case OCULUS: return TEXT("OCULUS");
		case DEV:    return TEXT("DEV");
		default:     return TEXT("UNKNOWN");
	}
}

class AuthHelper
{
public:
	static UE::Online::FAuthLogin::Params GetAuthParams(Platform Platform, const FString& Token);
	static IExternalTokenProvider* CreateTokenProvider(Platform Platform, UGameInstance* GameInstance);
};
