// Copyright Epic Games, Inc. All Rights Reserved.


#include "Simple_ShooterGameModeBase.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"

void ASimple_ShooterGameModeBase::EndGame(bool bIsWin)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		Controller->GameHasEnded(Controller->GetPawn(), bIsWin);
	}
}