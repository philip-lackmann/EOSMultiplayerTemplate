// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERTEMPLATE_API UOnlineGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
protected:
	virtual void OnStart() override;
	
	virtual void Shutdown() override;

private:
	UFUNCTION()
	void Authenticate();
};
