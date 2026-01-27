#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Misc/ConfigCacheIni.h"
#include "OnlineServicesProjectSettings.generated.h"

UCLASS(Config=Engine, DefaultConfig, meta=(DisplayName="Online Services"))
class MULTIPLAYERTEMPLATE_API UOnlineServicesProjectSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UOnlineServicesProjectSettings()
	{
		DefaultServices = TEXT("Null");
	}

	// Project Settings category
	virtual FName GetCategoryName() const override { return FName(TEXT("Project")); }
	virtual FText GetSectionText() const override { return FText::FromString(TEXT("Online Services")); }
	virtual FText GetSectionDescription() const override
	{
		return FText::FromString(TEXT("Configure the [OnlineServices] DefaultServices entry stored in DefaultEngine.ini"));
	}

	// Read the real value from [OnlineServices] when the settings object is loaded
	virtual void PostInitProperties() override
	{
		Super::PostInitProperties();

		FString FromIni;
		if (GConfig && GConfig->GetString(TEXT("OnlineServices"), TEXT("DefaultServices"), FromIni, GEngineIni))
		{
			if (!FromIni.IsEmpty())
			{
				DefaultServices = FromIni;
			}
		}
	}

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override
	{
		Super::PostEditChangeProperty(PropertyChangedEvent);

		// Write ONLY to [OnlineServices] in DefaultEngine.ini (GEngineIni points at DefaultEngine.ini in editor)
		if (GConfig)
		{
			GConfig->SetString(TEXT("OnlineServices"), TEXT("DefaultServices"), *DefaultServices, GEngineIni);

			GConfig->Flush(false, GEngineIni);
		}
	}
#endif

public:
	/** UI value that we manually persist to [OnlineServices] DefaultServices */
	UPROPERTY(EditAnywhere, Category="OnlineServices", meta=(DisplayName="Default Services"))
	FString DefaultServices;
};
