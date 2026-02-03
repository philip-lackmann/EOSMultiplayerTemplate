#include "OculusTokenProvider.h"

#if PLATFORM_ANDROID
#include "OVR_Message.h"
#include "OVRPlatformRequests.h"
#include "OVRPlatformSubsystem.h"
#endif

void OculusTokenProvider::GetToken(TFunction<void(bool bOk, const FString& Token)> Callback)
{
#if PLATFORM_ANDROID
	UGameInstance* GI = GameInstance.Get();
	if (!GI)
	{
		UE_LOG(LogTemp, Error, TEXT("[OculusToken] No GameInstance"));
		Callback(false, TEXT(""));
		return;
	}

	UOvrPlatformSubsystem* PlatformSubsys = GI->GetSubsystem<UOvrPlatformSubsystem>();
	if (!PlatformSubsys)
	{
		UE_LOG(LogTemp, Error, TEXT("[OculusToken] UOvrPlatformSubsystem not available (Meta Platform SDK plugin not initialized?)"));
		Callback(false, TEXT(""));
		return;
	}

	// Start message pumping once (required for request delegates to fire). :contentReference[oaicite:3]{index=3}
	if (!bStartedPump)
	{
		PlatformSubsys->StartMessagePump();
		bStartedPump = true;
	}

	// Get Oculus UserID.
	// This is the stable C API call. If it returns 0, platform isn't ready / entitlement not done / not on device.
	const uint64 UserId = (uint64)ovr_GetLoggedInUserID();
	if (UserId == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("[OculusToken] ovr_GetLoggedInUserID == 0 (platform not ready / not logged in / not entitled)"));
		Callback(false, TEXT(""));
		return;
	}

	// Request the UserProof (nonce)
	const ovrRequest ReqId = ovr_User_GetUserProof();
	if (ReqId == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("[OculusToken] User_GetUserProof() returned invalid request id"));
		Callback(false, TEXT(""));
		return;
	}

	// Register callback for this request id
	PlatformSubsys->AddRequestDelegate(
		ReqId,
		FOvrPlatformMessageOnComplete::CreateLambda(
			[UserId, Callback = MoveTemp(Callback)](const TOvrMessageHandlePtr& MessagePtr, const bool bIsError)
			{
				const ovrMessageHandle Message = *MessagePtr;

				if (bIsError || !Message || ovr_Message_IsError(Message))
				{
					UE_LOG(LogTemp, Error, TEXT("[OculusToken] User_GetUserProof failed"));
					Callback(false, TEXT(""));
					return;
				}

				const ovrUserProofHandle Proof = ovr_Message_GetUserProof(Message);
				if (!Proof)
				{
					UE_LOG(LogTemp, Error, TEXT("[OculusToken] No UserProof in response"));
					Callback(false, TEXT(""));
					return;
				}

				const char* NonceC = ovr_UserProof_GetNonce(Proof);
				const FString Nonce = UTF8_TO_TCHAR(NonceC ? NonceC : "");

				if (Nonce.IsEmpty())
				{
					UE_LOG(LogTemp, Error, TEXT("[OculusToken] UserProof nonce was empty"));
					Callback(false, TEXT(""));
					return;
				}

				const FString Token = FString::Printf(TEXT("%llu|%s"), UserId, *Nonce);
				Callback(true, Token);
			}
		)
	);
#else
	UE_LOG(LogTemp, Error, TEXT("[OculusToken] OculusTokenProvider::GetToken"));
	Callback(false, TEXT(""));
#endif
}
