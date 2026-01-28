// Fill out your copyright notice in the Description page of Project Settings.


#include "OnlineGameInstance.h"

#include "OnlineAuthSubsystem.h"
#include "OnlineIdentityHelper.h"

void UOnlineGameInstance::Init()
{
	Super::Init();
	
	OnLocalPlayerAddedEvent.AddUObject(this, &UOnlineGameInstance::HandleLocalPlayerAdded);
}

void UOnlineGameInstance::Shutdown()
{
	Super::Shutdown();
}

UOnlineGameInstance::UOnlineGameInstance(const FObjectInitializer& ObjectInitializer)
{
	
}

void UOnlineGameInstance::HandleLocalPlayerAdded(ULocalPlayer* NewPlayer)
{
	if (UOnlineAuthSubsystem* Auth = GetSubsystem<UOnlineAuthSubsystem>())
	{
		// Auth->LoginWithDevAuthTool(TEXT("localhost:8081"), TEXT("Dev"));
		OnlineIdentityHelper::GetSteamWebApiTicket(GetWorld(), [Auth](bool bOk, const FString& Ticket)
		{
			if (!bOk) return;
			Auth->LoginWithSteamTicket(Ticket);
		});
	}
	OnLocalPlayerAddedEvent.RemoveAll(this);
}
