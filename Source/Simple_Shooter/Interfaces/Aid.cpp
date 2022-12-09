// Fill out your copyright notice in the Description page of Project Settings.


#include "Aid.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Simple_Shooter/ShooterCharacter.h"
#include "Components/WidgetComponent.h"

// Sets default values
AAid::AAid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = SceneComp;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);

	InteractWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractWidget"));
	InteractWidget->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AAid::BeginPlay()
{
	Super::BeginPlay();
	InteractWidget->SetVisibility(false);
	UE_LOG(LogTemp, Warning, TEXT("false"));
}

// Called every frame
void AAid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAid::InteractWithMe()
{
	AShooterCharacter* Character = Cast<AShooterCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (Character)
	{
		Character->AddAid();
		Destroy();
	}

}

void AAid::ShowInteractWidget()
{
	InteractWidget->SetVisibility(true);
}

void AAid::HideInteractWidget()
{
	InteractWidget->SetVisibility(false);
}

