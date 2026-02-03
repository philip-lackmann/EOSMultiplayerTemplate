#pragma once
#include "IExternalTokenProvider.h"

class UGameInstance;


class OculusTokenProvider : public IExternalTokenProvider
{
public:
	explicit OculusTokenProvider(UGameInstance* InGI) : GameInstance(InGI) {}
	virtual void GetToken(TFunction<void(bool bOk, const FString& Token)> Callback) override;
	
private:
	TWeakObjectPtr<UGameInstance> GameInstance;
	bool bStartedPump = false;
};
