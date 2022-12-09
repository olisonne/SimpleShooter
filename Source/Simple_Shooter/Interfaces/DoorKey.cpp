// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorKey.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "Simple_Shooter/ShooterCharacter.h"

// Sets default values
ADoorKey::ADoorKey()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADoorKey::BeginPlay()
{
	Super::BeginPlay();
}


void ADoorKey::InteractWithMe()
{
	OpenDoor();
}



