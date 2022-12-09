// Fill out your copyright notice in the Description page of Project Settings.


#include "WantedInfo.h"
#include "FinishDoor.h"
#include "Kismet/GameplayStatics.h"
#include "Simple_Shooter/ShooterCharacter.h"

void AWantedInfo::InteractWithMe()
{
	TArray<AActor*> finishDoors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFinishDoor::StaticClass(), finishDoors);
	for (int i = 0; i<finishDoors.Num(); ++i)
	{
		finishDoors[i]->Destroy();
		this->Destroy();
		AShooterCharacter* Character = Cast<AShooterCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
		if (Character)
		{
			Character->SetObjective("Find Exit");
		}
	}
}
