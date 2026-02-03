// Fill out your copyright notice in the Description page of Project Settings.


#include "OnlineGameInstance.h"

#include "OnlineAuthSubsystem.h"
#include "IdentityProvider/AuthHelper.h"
#include "IdentityProvider/IExternalTokenProvider.h"

void UOnlineGameInstance::OnStart()
{
	Super::OnStart();
	UE_LOG(LogTemp, Log, TEXT("UOnlineGameInstance::OnStart"));
	
	this->Authenticate();
}

void UOnlineGameInstance::Shutdown()
{
	Super::Shutdown();
}

void UOnlineGameInstance::Authenticate()
{
	UE_LOG(LogTemp, Log, TEXT("UOnlineGameInstance::Authenticate"));
	
	UOnlineAuthSubsystem* Auth = GetSubsystem<UOnlineAuthSubsystem>();
	if (!Auth)
	{
		UE_LOG(LogTemp, Error, TEXT("[Auth] OnlineAuthSubsystem is null"));
	}
	
	constexpr Platform Platform = DEV; // TODO: some config shizzle
	IExternalTokenProvider* TokenProvider = AuthHelper::CreateTokenProvider(Platform, this);
	
	if (!TokenProvider)
	{
		UE_LOG(LogTemp, Error, TEXT("[Auth] TokenProvider is null"));
		return;
	}
	
	TokenProvider->GetToken([Auth, Platform](bool bOk, const FString& Token)
	{
		if (!bOk)
		{
			UE_LOG(LogTemp, Error, TEXT("[Auth] Failed retrieving a token for login. Platform: %s"), *PlatformToString(Platform));
			return;
		}
		Auth->LoginWithExternalToken(Platform, Token);
	});	
}
