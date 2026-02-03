#pragma once

class IExternalTokenProvider
{
public:
	virtual ~IExternalTokenProvider() = default;
	virtual void GetToken(TFunction<void(bool bOk, const FString& Token)> Callback) = 0;
};
