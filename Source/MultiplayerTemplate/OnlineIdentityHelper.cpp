#include "OnlineIdentityHelper.h"
#include "OnlineSubsystemUtils.h"

void OnlineIdentityHelper::GetSteamWebApiTicket(UWorld* World, TFunction<void(bool bOk, const FString& Ticket)> Callback)
{
	
	if (!FModuleManager::Get().LoadModule("OnlineSubsystemSteam"))
	{
		UE_LOG(LogTemp, Error, TEXT("[SteamTicket] OnlineSubsystemSteam module failed to load"));
	}
	
	IOnlineSubsystem* SteamSubsystem = Online::GetSubsystem(World, STEAM_SUBSYSTEM);
	if (!SteamSubsystem)
	{
		UE_LOG(LogTemp, Error, TEXT("[SteamTicket] Steam subsystem is null."));
		Callback(false, TEXT(""));
		return;
	}

	IOnlineIdentityPtr Identity = SteamSubsystem->GetIdentityInterface();
	if (!Identity.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("[SteamTicket] Steam identity interface is null."));
		Callback(false, TEXT(""));
		return;
	}
	
	const int32 LocalUserNum = 0;
	
	FDelegateHandle LoginDelegateHandle = Identity->OnLoginCompleteDelegates->AddLambda(
		[Identity, Callback, LocalUserNum, LoginDelegateHandle, SteamSubsystem](int32 UserNum, bool bSuccess, const FUniqueNetId& UserId, const FString& Error)
		{
			Identity->OnLoginCompleteDelegates->Remove(LoginDelegateHandle);
			
			if (!bSuccess)
			{
				UE_LOG(LogTemp, Error, TEXT("[SteamTicket] Steam login failed: %s"), *Error);
				Callback(false, TEXT(""));
				return;
			}

			UE_LOG(LogTemp, Display, TEXT("[SteamTicket] Steam login OK."));
			
			// "WebAPI:<SteamNetworkingIdentity>"
			const FString TokenRequest = TEXT("WebAPI:epiconlineservices");

			Identity->GetLinkedAccountAuthToken(
				LocalUserNum,
				TokenRequest,
				IOnlineIdentity::FOnGetLinkedAccountAuthTokenCompleteDelegate::CreateLambda(
					[Callback](int32 Num, bool bWasSuccessful, const FExternalAuthToken& AuthToken)
					{
						if (!bWasSuccessful)
						{
							UE_LOG(LogTemp, Error, TEXT("[SteamTicket] Failed to get WebAPI ticket."));
							Callback(false, TEXT(""));
							return;
						}

						UE_LOG(LogTemp, Display, TEXT("[SteamTicket] Ticket OK."));
						Callback(true, AuthToken.TokenString);
					}
				)
			);
		}
	);
	
	if (!Identity->AutoLogin(LocalUserNum))
	{
		UE_LOG(LogTemp, Warning, TEXT("[SteamTicket] AutoLogin not supported, using Login instead…"));

		Identity->Login(LocalUserNum, FOnlineAccountCredentials{}); // anonymous Steam login
	}
}
