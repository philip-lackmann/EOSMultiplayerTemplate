#pragma once
#include "IExternalTokenProvider.h"

class DevTokenProvider : public IExternalTokenProvider
{
public:
	virtual void GetToken(TFunction<void(bool bOk, const FString& Token)> Callback) override;
};
