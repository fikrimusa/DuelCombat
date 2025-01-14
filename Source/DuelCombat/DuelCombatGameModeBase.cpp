#include "DuelCombatGameModeBase.h"
#include "HttpHandler.h"
#include "GameFramework/PlayerController.h"

ADuelCombatGameModeBase::ADuelCombatGameModeBase()
{
	httpHandlerInstance = nullptr;
}

void ADuelCombatGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (NewPlayer)
	{
		FString PlayerName = NewPlayer->GetName();
		FString PlayerEmail = TEXT("SY@example.com");
		FString DisplayName = TEXT("SY");

		UE_LOG(LogTemp, Warning, TEXT("Player Email: %s"), *PlayerEmail);
		UE_LOG(LogTemp, Warning, TEXT("Display Name: %s"), *DisplayName);
		UE_LOG(LogTemp, Warning, TEXT("Player logged in: %s"), *PlayerName);
		
		if (httpHandlerInstance)
		{
			// Pass a lambda or callback to handle the result
			httpHandlerInstance->SendAccountToBackend(PlayerName, PlayerEmail, DisplayName,
				[this](bool bSuccess) {
					// Log inside the lambda to confirm it's called
					UE_LOG(LogTemp, Warning, TEXT("Callback triggered with success: %d"), bSuccess);
					OnAccountSent(bSuccess); // Handle the result
				});
		}

	}
}

void ADuelCombatGameModeBase::OnAccountSent(bool bSuccess)
{
	if (bSuccess)
	{
		UE_LOG(LogTemp, Warning, TEXT("Successfully sent player data to backend."));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to send player data to backend."));
	}
}


void ADuelCombatGameModeBase::SetHttpHandler(UHttpHandler* NewHttpHandler)
{
	httpHandlerInstance = NewHttpHandler;
}