#pragma once

class OnlineIdentityHelper
{
public:
	static void GetSteamWebApiTicket(UWorld* World, TFunction<void(bool bOk, const FString& Ticket)> Callback);
};
