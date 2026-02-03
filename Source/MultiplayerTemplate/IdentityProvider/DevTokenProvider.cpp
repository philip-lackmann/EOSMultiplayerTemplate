#include "DevTokenProvider.h"

void DevTokenProvider::GetToken(TFunction<void(bool bOk, const FString& Token)> Callback)
{
	Callback(true, TEXT("Dev"));
}
