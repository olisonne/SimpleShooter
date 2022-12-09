// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletsBox.h"
#include "Kismet/GameplayStatics.h"
#include "Simple_Shooter/ShooterCharacter.h"

// Sets default values
ABulletsBox::ABulletsBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABulletsBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABulletsBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABulletsBox::InteractWithMe()
{
	AShooterCharacter* Character = Cast<AShooterCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (Character)
	{
		Character->AddBullet(value);
		Destroy();
	}
}
