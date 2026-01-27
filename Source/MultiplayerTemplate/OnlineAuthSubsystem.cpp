// Fill out your copyright notice in the Description page of Project Settings.

#include "OnlineAuthSubsystem.h"
#include "Online/Auth.h"
#include "Online/OnlineResult.h"
#include "Online/OnlineError.h"
#include "Online/OnlineAsyncOpHandle.h"

void UOnlineAuthSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	Services = UE::Online::GetServices();
	if (!Services)
	{
		UE_LOG(LogTemp, Error, TEXT("Auth failed: GetServices() returned null. Check DefaultEngine.ini for [OnlineServices] DefaultServices=Epic."));
		return;
	}
	
	Auth = Services->GetAuthInterface();
	if (!Auth)
	{
		UE_LOG(LogTemp, Error, TEXT("Auth failed: Auth interface not available. Ensure OnlineServicesEOSGS/EOS plugins enabled & configured."));
		return;
	}
}

void UOnlineAuthSubsystem::LoginWithDevAuthTool(const FString& HostAndPort, const FString& CredentialName)
{
	if (!Auth) return;
	
	const ULocalPlayer* Player = GetGameInstance()->GetFirstGamePlayer();
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("Auth failed: No LocalPlayer yet; cannot login."));
		return;
	}
	
	UE::Online::FAuthLogin::Params Params;
	Params.PlatformUserId = Player->GetPlatformUserId();
	
	Params.CredentialsType = UE::Online::LoginCredentialsType::Developer;
	Params.CredentialsId = HostAndPort;
	Params.CredentialsToken.Emplace<FString>(CredentialName);
	
	Auth->Login(MoveTemp(Params)).OnComplete(
		[this](const UE::Online::TOnlineResult<UE::Online::FAuthLogin>& Result)
		{
			OnLoginComplete(Result);
		}
	);
}

void UOnlineAuthSubsystem::OnLoginComplete(const UE::Online::TOnlineResult<UE::Online::FAuthLogin>& Result)
{
	if (Result.IsOk())
	{
		const UE::Online::FAuthLogin::Result& R = Result.GetOkValue();
		this->bLoggedIn = true;
		this->AccountId = R.AccountInfo->AccountId;

		UE_LOG(LogTemp, Display, TEXT("Auth success: Login successful."));
	}
	else
	{
		this->bLoggedIn = false;
		this->AccountId = UE::Online::FAccountId();

		const auto& Err = Result.GetErrorValue();
		UE_LOG(LogTemp, Error, TEXT("Auth failed: %s"), *Err.GetLogString());
	}
}
