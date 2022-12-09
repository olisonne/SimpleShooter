// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLE_SHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LoseScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> WinScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HUDClass;

	UPROPERTY(EditAnywhere)
	float RestartDelay = 5.f;

	FTimerHandle TimerHandle_RestartTimer;

	UUserWidget* HUD;

protected:

	virtual void BeginPlay() override;


public:

	virtual void GameHasEnded(class AActor* EndGameFocus, bool bIsWinner) override;
};
