// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Aid.h"
#include "Elevator.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLE_SHOOTER_API AElevator : public AAid
{
	GENERATED_BODY()

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void InteractWithMe() override;

private:

	UPROPERTY(EditAnywhere)
		FVector HighLevel;

	UPROPERTY(EditAnywhere)
		FVector LowLevel;

	bool bCanInteract = true;

	float TimeElapsed = 0.f;

	float LerpDuration = 3.f;

	float InterpSpeed = 0.5f;

	bool bMoveUp = false;
	bool bMoveDown = false;

	void Move(float DeltaTime, FVector NewLocation);
	
};
