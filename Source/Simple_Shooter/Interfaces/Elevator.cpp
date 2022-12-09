// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "Elevator.h"

void AElevator::InteractWithMe()
{
	if (bCanInteract)
	{
		if (GetActorLocation().Equals(HighLevel))
		{
			bMoveDown = true;
		}
		else
		{
			bMoveUp = true;
		}
	}
}

void AElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bMoveUp)
	{
		Move(DeltaTime, HighLevel);;
	}
	else if (bMoveDown)
	{
		Move(DeltaTime, LowLevel);
	}

}

void AElevator::Move(float DeltaTime, FVector NewLocation)
{
	bCanInteract = false;
	InteractWidget->SetVisibility(false);
	if (TimeElapsed < LerpDuration)
	{
		SetActorLocation(FMath::Lerp(GetActorLocation(), NewLocation, TimeElapsed / LerpDuration));
		TimeElapsed += DeltaTime;
	}

	if (GetActorLocation().Equals(NewLocation))
	{
		bMoveUp = false;
		bMoveDown = false;
		bCanInteract = true;
		TimeElapsed = 0.f;
	}
}

