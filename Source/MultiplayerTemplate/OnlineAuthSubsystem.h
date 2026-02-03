// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IdentityProvider/AuthHelper.h"
#include "Online/Auth.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Online/OnlineServices.h"
#include "OnlineAuthSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERTEMPLATE_API UOnlineAuthSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	void LoginWithExternalToken(Platform Platform, const FString& Token);

	bool IsLoggedIn() const { return bLoggedIn; }
	UE::Online::FAccountId GetAccountId() const { return AccountId; }

private:
	UE::Online::IOnlineServicesPtr Services;
	UE::Online::IAuthPtr Auth;

	bool bLoggedIn = false;
	UE::Online::FAccountId AccountId;

	void OnLoginComplete(const UE::Online::TOnlineResult<UE::Online::FAuthLogin>& Result);
};
