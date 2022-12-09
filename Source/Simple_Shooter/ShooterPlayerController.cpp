// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"
void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HUD = CreateWidget(this, HUDClass);
	if (HUD)
	{
		HUD->AddToViewport();
	}
}


void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetCharacter());

	if (ControlledCharacter)
	{
		ControlledCharacter->SetObjective("");
	}

	if (bIsWinner)
	{
		UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
		if (WinScreen)
		{
			WinScreen->AddToViewport();
		}
		
	}
	else
	{
		UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
		if (LoseScreen)
		{
			LoseScreen->AddToViewport();
		}
	}

}
