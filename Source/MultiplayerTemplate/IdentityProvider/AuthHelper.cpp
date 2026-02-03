#include "AuthHelper.h"

#include "DevTokenProvider.h"
#include "OculusTokenProvider.h"
#include "SteamTokenProvider.h"

UE::Online::FAuthLogin::Params AuthHelper::GetAuthParams(const Platform Platform, const FString& Token)
{
	UE::Online::FAuthLogin::Params Params;
	Params.CredentialsType = UE::Online::LoginCredentialsType::ExternalAuth;
	
	switch (Platform)
	{
		case DEV:
			Params.CredentialsType = UE::Online::LoginCredentialsType::Developer;
			Params.CredentialsId = TEXT("localhost:8081"); // TODO: some config shizzle
			Params.CredentialsToken.Emplace<FString>(Token);
			break;
		case STEAM:
			Params.CredentialsType = UE::Online::LoginCredentialsType::ExternalAuth;
			Params.CredentialsToken.Set<UE::Online::FExternalAuthToken>({
				.Type = UE::Online::ExternalLoginType::SteamSessionTicket,
				.Data = Token,
			});
			break;
		case OCULUS:
			Params.CredentialsType = UE::Online::LoginCredentialsType::ExternalAuth;
			Params.CredentialsToken.Set<UE::Online::FExternalAuthToken>({
				.Type = UE::Online::ExternalLoginType::OculusUserIdNonce,
				.Data = Token,
			});
			break;
	}
	
	return Params;
}

IExternalTokenProvider* AuthHelper::CreateTokenProvider(const Platform Platform, UGameInstance* GameInstance)
{
	switch (Platform)
	{
		case STEAM:
			return new SteamTokenProvider();
		case OCULUS:
			return new OculusTokenProvider(GameInstance);
		case DEV:
			return new DevTokenProvider();
		default:
			return nullptr;
	}
}
