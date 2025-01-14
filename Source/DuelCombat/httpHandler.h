#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "http.h"
#include "Interfaces/IHttpResponse.h"
#include "Json.h"
#include "HttpHandler.generated.h"

class IHttpRequest;
class IHttpResponse;

UCLASS()
class DUELCOMBAT_API UHttpHandler : public UObject
{
	GENERATED_BODY()

public:
	UHttpHandler();

	// Function to send player account data to the backend
	void SendAccountToBackend(const FString& Username, const FString& Email, const FString& DisplayName, TFunction<void(bool)> Callback);

private:
	// Callback function to notify the completion of account creation
	void OnCreateAccountResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// Variable to store the callback function
	TFunction<void(bool)> AccountCallback;
};
