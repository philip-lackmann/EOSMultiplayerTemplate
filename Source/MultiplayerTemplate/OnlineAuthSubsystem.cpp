// Fill out your copyright notice in the Description page of Project Settings.

#include "OnlineAuthSubsystem.h"

#include "eos_connect.h"
#include "IdentityProvider/AuthHelper.h"
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
		UE_LOG(LogTemp, Error, TEXT("[Auth] GetServices() returned null. Check DefaultEngine.ini for [OnlineServices] DefaultServices=Epic."));
		return;
	}
	
	Auth = Services->GetAuthInterface();
	if (!Auth)
	{
		UE_LOG(LogTemp, Error, TEXT("[Auth] Auth interface not available. Ensure OnlineServicesEOSGS/EOS plugins enabled & configured."));
		return;
	}
}

void UOnlineAuthSubsystem::LoginWithExternalToken(Platform Platform, const FString& Token)
{
	if (!Auth) return;

	const ULocalPlayer* Player = GetGameInstance()->GetFirstGamePlayer();
	if (!Player)
	{
		UE_LOG(LogTemp, Error, TEXT("[Auth] No LocalPlayer yet; cannot login."));
		return;
	}
	
	UE::Online::FAuthLogin::Params Params = AuthHelper::GetAuthParams(Platform, Token);
	Params.PlatformUserId = Player->GetPlatformUserId();
	
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

		UE_LOG(LogTemp, Display, TEXT("[Auth] Login successful."));
	}
	else
	{
		this->bLoggedIn = false;
		this->AccountId = UE::Online::FAccountId();

		const auto& Err = Result.GetErrorValue();
		UE_LOG(LogTemp, Error, TEXT("[Auth] %s"), *Err.GetLogString());
	}
}
