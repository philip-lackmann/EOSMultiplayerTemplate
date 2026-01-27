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
	 
	/** Called to initialize game instance on game startup */
	virtual void Init() override;
	
	/** Called to shutdown game instance on game exit */
	virtual void Shutdown() override;
	
public:
	 
	/** Called to initialize game instance object */
	UOnlineGameInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
private:
	UFUNCTION()
	void HandleLocalPlayerAdded(ULocalPlayer* NewPlayer);
};
