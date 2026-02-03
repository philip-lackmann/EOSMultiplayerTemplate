#pragma once
#include "IExternalTokenProvider.h"

class SteamTokenProvider : public IExternalTokenProvider
{
public:
	virtual void GetToken(TFunction<void(bool bOk, const FString& Token)> Callback) override;
};
