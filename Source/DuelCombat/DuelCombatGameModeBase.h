#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DuelCombatGameModeBase.generated.h"

class UHttpHandler;

/**
 * ADuelCombatGameModeBase class handles the game mode logic for Duel Combat.
 * It inherits from AGameModeBase to customize the behavior for this specific game mode.
 */
UCLASS()
class DUELCOMBAT_API ADuelCombatGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADuelCombatGameModeBase();

	virtual void PostLogin(APlayerController* NewPlayer) override;
	void OnAccountSent(bool bSuccess);
	void SetHttpHandler(UHttpHandler* NewHttpHandler);

private:
	UHttpHandler* httpHandlerInstance;
};
